/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * wiiu_structs.h: Nintendo Wii U data structures.                         *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include <stdint.h>
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Nintendo Wii U disc header. (Retail games only!)
 * Reference: https://github.com/maki-chan/wudecrypt/blob/master/main.c
 * 
 * All fields are big-endian.
 * NOTE: Strings are NOT null-terminated!
 */
#pragma pack(1)	// NOTE: Some compilers pad this structure to a multiple of 4 bytes
#define WIIU_MAGIC 'WUP-'
typedef struct _WiiU_DiscHeader {
	union PACKED {
		uint32_t magic;		// 'WUP-'
		char id[10];		// "WUP-P-xxxx"
		struct PACKED {
			char wup[3];	// "WUP"
			char hyphen1;	// '-'
			char p;		// 'P'
			char hyphen2;	// '-'
			char id4[4];	// "xxxx"
		};
	};
	char hyphen3;
	char version[2];	// Version number, in ASCII. (e.g. "00")
	char hyphen4;
	char os_version[3];	// Required OS version, in ASCII. (e.g. "551")
	char region[3];		// Region code, in ASCII. ("USA", "EUR") (TODO: Is this the enforced region?)
	char hyphen5;
	char disc_number;	// Disc number, in ASCII. (TODO: Verify?)
} WiiU_DiscHeader;
ASSERT_STRUCT(WiiU_DiscHeader, 22);
#pragma pack()

// Secondary Wii U disc magic at 0x10000.
#define WIIU_SECONDARY_MAGIC 0xCC549EB9

#ifdef __cplusplus
}
#endif
