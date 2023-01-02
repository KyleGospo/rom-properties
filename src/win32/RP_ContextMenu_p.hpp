/***************************************************************************
 * ROM Properties Page shell extension. (Win32)                            *
 * RP_ContextMenu_p.hpp: IContextMenu implementation. (PRIVATE CLASS)      *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "RP_ContextMenu.hpp"

// C++ includes
#include <string>
#include <vector>

// TCHAR
#include "tcharx.h"

// Workaround for RP_D() expecting the no-underscore naming convention.
#define RP_ContextMenuPrivate RP_ContextMenu_Private

// CLSID
extern const CLSID CLSID_RP_ContextMenu;

class RP_ContextMenu_Private
{
	public:
		RP_ContextMenu_Private();
		~RP_ContextMenu_Private();

	private:
		RP_DISABLE_COPY(RP_ContextMenu_Private)

	public:
		// Selected filenames. [from IShellExtInit::Initialize()]
		// NOTE: Ownership passes to convert_to_png_ThreadProc()
		// once the command is invoked.
		std::vector<LPTSTR> *filenames;

		/**
		 * Clear a filenames vector.
		 * All filenames will be deleted and the vector will also be deleted.
		 * @param filenames Filenames vector
		 */
		static void clear_filenames_vector(std::vector<LPTSTR> *filenames);

		/**
		 * Convert a texture file to PNG format.
		 * Destination filename will be generated based on the source filename.
		 * @param source_file Source filename
		 * @return 0 on success; non-zero on error.
		 */
		static int convert_to_png(LPCTSTR source_file);

		/**
		 * Convert texture file(s) to PNG format.
		 * This function should be created in a separate thread using _beginthreadex().
		 * @param lpParameter [in] Pointer to vector of filenames. Will be freed by this function afterwards.
		 * @return 0 on success; non-zero on error.
		 */
		static unsigned int WINAPI convert_to_png_ThreadProc(std::vector<LPTSTR> *filenames);

	public:
		/**
		 * Register the file type handler.
		 *
		 * Internal version; this only registers for a single Classes key.
		 * Called by the public version multiple times if a ProgID is registered.
		 *
		 * @param hkey_Assoc File association key to register under.
		 * @return ERROR_SUCCESS on success; Win32 error code on error.
		 */
		static LONG RegisterFileType(LibWin32UI::RegKey &hkey_Assoc);

		/**
		 * Unregister the file type handler.
		 *
		 * Internal version; this only unregisters for a single Classes key.
		 * Called by the public version multiple times if a ProgID is registered.
		 *
		 * @param hkey_Assoc File association key to unregister under.
		 * @return ERROR_SUCCESS on success; Win32 error code on error.
		 */
		static LONG UnregisterFileType(LibWin32UI::RegKey &hkey_Assoc);
};
