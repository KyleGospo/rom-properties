/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * MachO.cpp: Mach-O executable format.                                    *
 *                                                                         *
 * Copyright (c) 2019-2021 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "stdafx.h"
#include "MachO.hpp"
#include "data/MachOData.hpp"
#include "macho_structs.h"

// librpbase, librpfile
using namespace LibRpBase;
using LibRpFile::IRpFile;

// C++ STL classes.
using std::string;
using std::vector;

// Uninitialized vector class.
// Reference: http://andreoffringa.org/?q=uvector
#include "uvector.h"

namespace LibRomData {

ROMDATA_IMPL(MachO)

class MachOPrivate final : public RomDataPrivate
{
	public:
		MachOPrivate(MachO *q, LibRpFile::IRpFile *file);

	private:
		typedef RomDataPrivate super;
		RP_DISABLE_COPY(MachOPrivate)

	public:
		// Executable format.
		enum class Exec_Format {
			Unknown	= -1,

			Mach	= 0,
			Fat	= 1,

			Max
		};
		Exec_Format execFormat;

		// Mach-O format.
		enum class Mach_Format : int8_t {
			Unknown = -1,

			_32LSB	= 0,
			_64LSB	= 1,
			_32MSB	= 2,
			_64MSB	= 3,

			Max,

			// Host/swap endian formats.

#if SYS_BYTEORDER == SYS_LIL_ENDIAN
			_32HOST	= _32LSB,
			_64HOST	= _64LSB,
			_32SWAP	= _32MSB,
			_64SWAP	= _64MSB,
#else /* SYS_BYTEORDER == SYS_BIG_ENDIAN */
			_32HOST	= _32MSB,
			_64HOST	= _64MSB,
			_32SWAP	= _32LSB,
			_64SWAP	= _64LSB,
#endif
		};

		// Maximum number of Mach-O headers to read.
		#define MAX_MACH_HEADERS 16U

		// Mach-O formats and headers.
		vector<Mach_Format> machFormats;
		ao::uvector<mach_header> machHeaders;

		/**
		 * Check the Mach-O magic number.
		 * @param magic Magic number as read directly from disk.
		 * @return Mach_Format value.
		 */
		static Mach_Format checkMachMagicNumber(uint32_t magic);
};

/** MachOPrivate **/

MachOPrivate::MachOPrivate(MachO *q, IRpFile *file)
	: super(q, file)
	, execFormat(Exec_Format::Unknown)
{ }

/**
 * Check the Mach-O magic number.
 * @param magic Magic number as read directly from disk.
 * @return Mach_Format value.
 */
MachOPrivate::Mach_Format MachOPrivate::checkMachMagicNumber(uint32_t magic)
{
	// NOTE: Checking in order of Mac OS X usage as of 2019.
	Mach_Format machFormat = Mach_Format::Unknown;
	if (magic == cpu_to_le32(MH_MAGIC_64)) {
		// LE64 magic number.
		machFormat = Mach_Format::_64LSB;
	} else if (magic == cpu_to_le32(MH_MAGIC)) {
		// LE32 magic number.
		machFormat = Mach_Format::_32LSB;
	} else if (magic == cpu_to_be32(MH_MAGIC)) {
		// BE32 magic number.
		machFormat = Mach_Format::_32MSB;
	} else if (magic == cpu_to_be32(MH_MAGIC_64)) {
		// BE64 magic number.
		machFormat = Mach_Format::_64MSB;
	}
	return machFormat;
}

/** MachO **/

/**
 * Read a Mach-O executable.
 *
 * A ROM file must be opened by the caller. The file handle
 * will be ref()'d and must be kept open in order to load
 * data from the ROM.
 *
 * To close the file, either delete this object or call close().
 *
 * NOTE: Check isValid() to determine if this is a valid ROM.
 *
 * @param file Open ROM image.
 */
MachO::MachO(IRpFile *file)
	: super(new MachOPrivate(this, file))
{
	// This class handles different types of files.
	// d->fileType will be set later.
	RP_D(MachO);
	d->className = "MachO";
	d->fileType = FileType::Unknown;

	if (!d->file) {
		// Could not ref() the file handle.
		return;
	}

	// Read the file header.
	// - Mach-O header: 7 DWORDs
	// - Universal header: 2 DWORDs, plus 5 DWORDs per architecture.
	// Assuming up to 16 architectures, read 2+(5*16) = 82 DWORDs, or 328 bytes.
	uint8_t header[(2+(5*MAX_MACH_HEADERS))*sizeof(uint32_t)];
	d->file->rewind();
	size_t size = d->file->read(header, sizeof(header));
	if (size != sizeof(header)) {
		UNREF_AND_NULL_NOCHK(d->file);
		return;
	}

	// Check if this executable is supported.
	DetectInfo info;
	info.header.addr = 0;
	info.header.size = sizeof(header);
	info.header.pData = header;
	info.ext = nullptr;	// Not needed for ELF.
	info.szFile = 0;	// Not needed for ELF.
	d->execFormat = static_cast<MachOPrivate::Exec_Format>(isRomSupported_static(&info));

	// Load the Mach header.
	switch (d->execFormat) {
		case MachOPrivate::Exec_Format::Mach:
			// Standard Mach executable.
			d->machFormats.resize(1);
			d->machHeaders.resize(1);
			memcpy(&d->machHeaders[0], header, sizeof(mach_header));
			d->machFormats[0] = d->checkMachMagicNumber(d->machHeaders[0].magic);
			d->isValid = ((int)d->machFormats[0] >= 0);
			break;

		case MachOPrivate::Exec_Format::Fat: {
			// Read up to 16 architectures.
			const fat_header *const fatHeader =
				reinterpret_cast<const fat_header*>(info.header.pData);
			const unsigned int nfat_arch = std::min<uint32_t>(
				MAX_MACH_HEADERS, be32_to_cpu(fatHeader->nfat_arch));
			d->machFormats.reserve(nfat_arch);
			d->machHeaders.reserve(nfat_arch);

			const fat_arch *fatArch =
				reinterpret_cast<const fat_arch*>(info.header.pData + 8);
			for (unsigned int i = 0; i < nfat_arch; i++, fatArch++) {
				const uint32_t offset = be32_to_cpu(fatArch->offset);
				if (offset < sizeof(fat_header)) {
					continue;
				}

				size_t idx = d->machFormats.size();
				d->machFormats.resize(idx+1);
				d->machHeaders.resize(idx+1);
				size_t size = d->file->seekAndRead(offset, &d->machHeaders[i], sizeof(mach_header));
				if (size == sizeof(mach_header)) {
					d->machFormats[idx] = d->checkMachMagicNumber(d->machHeaders[idx].magic);
				} else {
					// Unable to read this header.
					// TODO: Show an error?
					d->machFormats.resize(idx);
					d->machHeaders.resize(idx);
				}
			}

			d->isValid = !d->machFormats.empty();
			break;
		}

		default:
			// Not supported.
			d->isValid = false;
			break;
	}

	if (d->machFormats.empty() || d->machHeaders.empty()) {
		// No headers...
		d->isValid = false;
	}

	if (!d->isValid) {
		d->execFormat = MachOPrivate::Exec_Format::Unknown;
		d->machFormats.clear();
		d->machHeaders.clear();
		UNREF_AND_NULL_NOCHK(d->file);
		return;
	}

	// Swap endianness if needed.
	assert(d->machFormats.size() == d->machHeaders.size());
	auto hdrIter = d->machHeaders.begin();
	const auto machFormats_cend = d->machFormats.cend();
	for (auto fmtIter = d->machFormats.cbegin();
	     fmtIter != machFormats_cend; ++fmtIter, ++hdrIter)
	{
		switch (*fmtIter) {
			default:
				// Invalid format. Continue anyway...
				break;

			case MachOPrivate::Mach_Format::_32HOST:
			case MachOPrivate::Mach_Format::_64HOST:
				// Host-endian. Nothing to do.
				break;

			case MachOPrivate::Mach_Format::_32SWAP:
			case MachOPrivate::Mach_Format::_64SWAP: {
				// Swapped endian.
				// NOTE: Not swapping the magic number.
				mach_header *const machHeader = &(*hdrIter);
				machHeader->cputype	= __swab32(machHeader->cputype);
				machHeader->cpusubtype	= __swab32(machHeader->cpusubtype);
				machHeader->filetype	= __swab32(machHeader->filetype);
				machHeader->ncmds	= __swab32(machHeader->ncmds);
				machHeader->sizeofcmds	= __swab32(machHeader->sizeofcmds);
				machHeader->flags	= __swab32(machHeader->flags);
				break;
			}
		}
	}

	// Determine the file and MIME types.
	// NOTE: This assumes all architectures have the same file type.
	static const uint8_t fileTypes_tbl[] = {
		(uint8_t)FileType::Unknown,		// 0
		(uint8_t)FileType::RelocatableObject,	// MH_OBJECT
		(uint8_t)FileType::Executable,		// MH_EXECUTE
		(uint8_t)FileType::SharedLibrary,	// MH_FVMLIB: "Fixed VM" library file. (TODO: Add a separate FTYPE?)
		(uint8_t)FileType::CoreDump,		// MH_CORE
		(uint8_t)FileType::Executable,		// MH_PRELOAD (TODO: Special FTYPE?)
		(uint8_t)FileType::SharedLibrary,	// MH_DYLIB
		(uint8_t)FileType::Unknown,		// MH_DYLINKER (TODO)
		(uint8_t)FileType::Bundle,		// MH_BUNDLE
		(uint8_t)FileType::Unknown,		// MH_DYLIB_STUB (TODO)
		(uint8_t)FileType::Unknown,		// MH_DSYM (TODO)
		(uint8_t)FileType::Unknown,		// MH_KEXT_BUNDLE (TODO)
	};
	static const char *const mimeTypes_tbl[] = {
		nullptr,				// 0
		"application/x-mach-object",		// MH_OBJECT
		"application/x-mach-executable",	// MH_EXECUTE
		"application/x-mach-sharedlib",		// MH_FVMLIB: "Fixed VM" library file. (TODO: Add a separate FTYPE?)
		"application/x-mach-core",		// MH_CORE
		"application/x-mach-executable",	// MH_PRELOAD (TODO: Special FTYPE?)
		"application/x-mach-sharedlib",		// MH_DYLIB
		nullptr,				// MH_DYLINKER (TODO)
		"application/x-mach-bundle",		// MH_BUNDLE
		nullptr,				// MH_DYLIB_STUB (TODO)
		nullptr,				// MH_DSYM (TODO)
		nullptr,				// MH_KEXT_BUNDLE (TODO)
	};

	// d->fileType is set to FileType::Unknown above, so only set it
	// if the filetype is known.
	bool mimeIsSet = false;
	if (d->execFormat == MachOPrivate::Exec_Format::Fat) {
		// Fat binary.
		d->mimeType = "application/x-mach-fat-binary";
		mimeIsSet = true;
	}
	if (d->machHeaders[0].filetype < ARRAY_SIZE(fileTypes_tbl)) {
		d->fileType = static_cast<RomData::FileType>(fileTypes_tbl[d->machHeaders[0].filetype]);
		if (!mimeIsSet) {
			d->mimeType = mimeTypes_tbl[d->machHeaders[0].filetype];
		}
	}
}

/** ROM detection functions. **/

/**
 * Is a ROM image supported by this class?
 * @param info DetectInfo containing ROM detection information.
 * @return Class-specific system ID (>= 0) if supported; -1 if not.
 */
int MachO::isRomSupported_static(const DetectInfo *info)
{
	// Read the file header.
	// - Mach-O header: 7 DWORDs
	// - Universal header: 2 DWORDs, plus 5 DWORDs per architecture.
	// Only the first two DWORDs are needed for identification.
	assert(info != nullptr);
	assert(info->header.pData != nullptr);
	assert(info->header.addr == 0);
	if (!info || !info->header.pData ||
	    info->header.addr != 0 ||
	    info->header.size < 8)
	{
		// Either no detection information was specified,
		// or the header is too small.
		return static_cast<int>(MachOPrivate::Exec_Format::Unknown);
	}

	const uint32_t *const pu32 =
		reinterpret_cast<const uint32_t*>(info->header.pData);

	// Check the magic number.
	// NOTE: Checking in order of Mac OS X usage as of 2019.
	MachOPrivate::Exec_Format execFormat;
	if (pu32[0] == cpu_to_be32(FAT_MAGIC)) {
		// Universal binary.
		// Note that this is the same magic number as Java classes,
		// so check the second value (number of architectures)
		// to verify. We're assuming a maximum of 16 architectures
		// per executable.
		if (be32_to_cpu(pu32[1]) <= 16) {
			// Mach-O universal binary.
			execFormat = MachOPrivate::Exec_Format::Fat;
		} else {
			// Not supported.
			execFormat = MachOPrivate::Exec_Format::Unknown;
		}
	} else if (MachOPrivate::checkMachMagicNumber(pu32[0]) !=
		   MachOPrivate::Mach_Format::Unknown)
	{
		// Mach-O executable.
		execFormat = MachOPrivate::Exec_Format::Mach;
	} else {
		// Not supported.
		execFormat = MachOPrivate::Exec_Format::Unknown;
	}

	return static_cast<int>(execFormat);
}

/**
 * Get the name of the system the loaded ROM is designed for.
 * @param type System name type. (See the SystemName enum.)
 * @return System name, or nullptr if type is invalid.
 */
const char *MachO::systemName(unsigned int type) const
{
	RP_D(const MachO);
	if (!d->isValid || !isSystemNameTypeValid(type))
		return nullptr;

	// Mach-O has the same name worldwide, so we can
	// ignore the region selection.
	// TODO: Identify the OS, or list that in the fields instead?
	static_assert(SYSNAME_TYPE_MASK == 3,
		"MachO::systemName() array index optimization needs to be updated.");

	static const char *const sysNames[4] = {
		"Mach Microkernel", "Mach", "Mach", nullptr
	};

	return sysNames[type & SYSNAME_TYPE_MASK];
}

/**
 * Get a list of all supported file extensions.
 * This is to be used for file type registration;
 * subclasses don't explicitly check the extension.
 *
 * NOTE: The extensions do not include the leading dot,
 * e.g. "bin" instead of ".bin".
 *
 * NOTE 2: The array and the strings in the array should
 * *not* be freed by the caller.
 *
 * @return NULL-terminated array of all supported file extensions, or nullptr on error.
 */
const char *const *MachO::supportedFileExtensions_static(void)
{
	static const char *const exts[] = {
		//".",		// FIXME: Does this work for files with no extension?
		".bin",
		".so",		// Shared libraries. (TODO: Versioned .so files.)
		".dylib",	// Dynamic libraries. (TODO: Versioned .dylib files.)
		".bundle",	// Bundles.
		// TODO: More?

		nullptr
	};
	return exts;
}

/**
 * Get a list of all supported MIME types.
 * This is to be used for metadata extractors that
 * must indicate which MIME types they support.
 *
 * NOTE: The array and the strings in the array should
 * *not* be freed by the caller.
 *
 * @return NULL-terminated array of all supported file extensions, or nullptr on error.
 */
const char *const *MachO::supportedMimeTypes_static(void)
{
	static const char *const mimeTypes[] = {
		// Unofficial MIME types.

		// FIXME: Defining the magic numbers for Mach-O
		// executables in rom-properties.xml causes
		// KDE to lock up due to a conflict with the
		// standard definitions. Hence, we're using our
		// own types.

		"application/x-mach-object",
		"application/x-mach-executable",
		"application/x-mach-sharedlib",
		"application/x-mach-core",
		"application/x-mach-bundle",
		"application/x-mach-fat-binary",

		nullptr
	};
	return mimeTypes;
}

/**
 * Load field data.
 * Called by RomData::fields() if the field data hasn't been loaded yet.
 * @return Number of fields read on success; negative POSIX error code on error.
 */
int MachO::loadFieldData(void)
{
	RP_D(MachO);
	if (!d->fields->empty()) {
		// Field data *has* been loaded...
		return 0;
	} else if (!d->file || !d->file->isOpen()) {
		// File isn't open.
		return -EBADF;
	} else if (!d->isValid) {
		// Unsupported file.
		return -EIO;
	}

	// Mach-O header.
	// TODO: Show multiple headers.
	if (d->machHeaders.empty()) {
		// No headers at all...
		return 0;
	}

	// Maximum of 4 fields per architecture.
	const int n_tabs = static_cast<int>(d->machHeaders.size());
	d->fields->reserve(4*n_tabs);
	d->fields->reserveTabs(n_tabs);

	int i = 0;
	auto fmtIter = d->machFormats.cbegin();
	const auto machHeaders_cend = d->machHeaders.cend();
	for (auto hdrIter = d->machHeaders.cbegin();
	     hdrIter != machHeaders_cend; ++hdrIter, ++fmtIter, i++)
	{
		const mach_header *const machHeader = &(*hdrIter);
		const MachOPrivate::Mach_Format machFormat = *fmtIter;

		// Use the CPU name for the tab title.
		const char *const s_cpu = MachOData::lookup_cpu_type(machHeader->cputype);

		// TODO: Change addTab() behavior to set the first tab's name?
		if (i == 0) {
			d->fields->setTabName(i, s_cpu ? s_cpu :
				rp_sprintf("0x%08X", machHeader->cputype).c_str());
		} else {
			d->fields->addTab(s_cpu ? s_cpu :
				rp_sprintf("0x%08X", machHeader->cputype).c_str());
		}

		// Executable format.
		static const char *const exec_type_tbl[] = {
			NOP_C_("RomData|ExecType", "32-bit Little-Endian"),
			NOP_C_("RomData|ExecType", "64-bit Little-Endian"),
			NOP_C_("RomData|ExecType", "32-bit Big-Endian"),
			NOP_C_("RomData|ExecType", "64-bit Big-Endian"),
		};
		const char *const format_title = C_("MachO", "Format");
		if (machFormat > MachOPrivate::Mach_Format::Unknown &&
		    (int)machFormat < ARRAY_SIZE_I(exec_type_tbl))
		{
			d->fields->addField_string(format_title,
				dpgettext_expr(RP_I18N_DOMAIN, "RomData|ExecType", exec_type_tbl[(int)machFormat]));
		} else {
			// TODO: Show individual values.
			// NOTE: This shouldn't happen...
			d->fields->addField_string(format_title, C_("RomData", "Unknown"));
		}

		// CPU type.
		const char *const cpu_title = C_("MachO", "CPU");
		if (s_cpu) {
			d->fields->addField_string(cpu_title, s_cpu);
		} else {
			d->fields->addField_string(cpu_title,
				rp_sprintf(C_("RomData", "Unknown (%u)"), machHeader->cputype & 0xFFFFFF));
		}

		// CPU subtype.
		const char *const s_cpu_subtype = MachOData::lookup_cpu_subtype(
			machHeader->cputype, machHeader->cpusubtype);
		if (s_cpu_subtype) {
			d->fields->addField_string(C_("MachO", "CPU Subtype"), s_cpu_subtype);
		}

		// Flags.
		// I/O support bitfield.
		static const char *const flags_bitfield_names[] = {
			// 0x00000000
			"NoUndefs", "IncrLink", "DyldLink", "BindAtLoad",
			// 0x00000010
			"Prebound", "SplitSegs", "LazyInit", "TwoLevel",
			// 0x00000100
			"ForceFlat", "NoMultiDefs", "NoFixPrebinding", "Prebindable",
			// 0x00001000
			"AllModsBound", "Subsections", "Canonical", "WeakDefines",
			// 0x00010000
			"BindsToWeak", "StackExec", "RootSafe", "SetuidSafe",
			// 0x00100000
			"NoReexport", "PIE", "DeadStrip", "TLVDescriptors",
			// 0x01000000
			"NoHeapExec", "AppExtSafe", "NListOutOfSync", "SimSupport",
			// 0x10000000
			nullptr, nullptr, nullptr, "DylibInCache",
		};
		vector<string> *const v_flags_bitfield_names = RomFields::strArrayToVector(
			flags_bitfield_names, ARRAY_SIZE(flags_bitfield_names));
		d->fields->addField_bitfield(C_("MachO", "Flags"),
			v_flags_bitfield_names, 3, machHeader->flags);
	}

	// Finished reading the field data.
	return static_cast<int>(d->fields->count());
}

}
