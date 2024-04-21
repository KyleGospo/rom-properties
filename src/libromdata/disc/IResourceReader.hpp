/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * IResourceReader.hpp: Interface for Windows resource readers.            *
 *                                                                         *
 * Copyright (c) 2016-2024 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "../Other/exe_res_structs.h"

// librpbase
#include "librpbase/disc/IPartition.hpp"

// C++ includes
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
// The Windows SDK is needed for LPCSTR/LPCWSTR.
#  include "libwin32common/RpWin32_sdk.h"
#endif /* _WIN32 */

namespace LibRomData {

class NOVTABLE IResourceReader : public LibRpBase::IPartition
{
protected:
	IResourceReader(const LibRpFile::IRpFilePtr &file)
		: super(file)
	{}
public:
	~IResourceReader() override = 0;

private:
	typedef LibRpBase::IPartition super;
	RP_DISABLE_COPY(IResourceReader)

public:
	/**
	 * DWORD alignment function.
	 * @param file	[in] File to DWORD align.
	 * @return 0 on success; non-zero on error.
	 */
	static int alignFileDWORD(LibRpFile::IRpFile *file);

public:
	/** Resource access functions **/

private:
	/**
	 * IPartition open() function.
	 * We don't want to use this one.
	 * @param filename Filename.
	 * @return IRpFile*, or nullptr on error.
	 */
	LibRpFile::IRpFilePtr open(const char *filename) final;

public:
	/**
	 * Open a resource.
	 * @param type Resource type ID
	 * @param id Resource ID (-1 for "first entry")
	 * @param lang Language ID (-1 for "first entry")
	 * @return IRpFile*, or nullptr on error.
	 */
	virtual LibRpFile::IRpFilePtr open(uint16_t type, int id, int lang) = 0;

#ifdef _WIN32
	/**
	 * Open a resource.
	 *
	 * Wrapper function for unusual cases in Windows builds where the
	 * resource type is wrapped using MAKEINTRESOURCEA().
	 *
	 * @param type Resource type ID
	 * @param id Resource ID (-1 for "first entry")
	 * @param lang Language ID (-1 for "first entry")
	 * @return IRpFile*, or nullptr on error.
	 */
	inline LibRpFile::IRpFilePtr open(LPCSTR type, int id, int lang)
	{
		return open(static_cast<uint16_t>(
			reinterpret_cast<uintptr_t>(type)), id, lang);
	}

	/**
	 * Open a resource.
	 *
	 * Wrapper function for unusual cases in Windows builds where the
	 * resource type is wrapped using MAKEINTRESOURCEW().
	 *
	 * @param type Resource type ID
	 * @param id Resource ID (-1 for "first entry")
	 * @param lang Language ID (-1 for "first entry")
	 * @return IRpFile*, or nullptr on error.
	 */
	inline LibRpFile::IRpFilePtr open(LPCWSTR type, int id, int lang)
	{
		return open(static_cast<uint16_t>(
			reinterpret_cast<uintptr_t>(type)), id, lang);
	}
#endif /* _WIN32 */

	// StringTable
	// - Element 1: Key
	// - Element 2: Value
	typedef std::vector<std::pair<std::string, std::string> > StringTable;

	// StringFileInfo section
	// - Key: Langauge ID. (LOWORD = charset, HIWORD = language)
	// - Value: String table.
	typedef std::unordered_map<uint32_t, StringTable> StringFileInfo;

	/**
	 * Load a VS_VERSION_INFO resource.
	 * Data will be byteswapped to host-endian if necessary.
	 *
	 * @param id		[in] Resource ID. (-1 for "first entry")
	 * @param lang		[in] Language ID. (-1 for "first entry")
	 * @param pVsFfi	[out] VS_FIXEDFILEINFO (host-endian)
	 * @param pVsSfi	[out] StringFileInfo section.
	 * @return 0 on success; non-zero on error.
	 */
	virtual int load_VS_VERSION_INFO(int id, int lang, VS_FIXEDFILEINFO *pVsFfi, StringFileInfo *pVsSfi) = 0;
};

typedef std::shared_ptr<IResourceReader> IResourceReaderPtr;

/**
 * Both gcc and MSVC fail to compile unless we provide
 * an empty implementation, even though the function is
 * declared as pure-virtual.
 */
inline IResourceReader::~IResourceReader() = default;

}
