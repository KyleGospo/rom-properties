/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * CBMData.hpp: Commodore cartridge data.                                  *
 *                                                                         *
 * Copyright (c) 2022 by David Korth.                                      *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "stdafx.h"
#include "CBMData.hpp"

namespace LibRomData { namespace CBMData {

/** Cartridge types are synchronized with VICE 3.6. **/
#include "CBM_C64_Cartridge_Type_data.h"

// VIC-20 cartridge types
static const std::array<const char*, 6> crt_types_vic20 = {{
	"generic cartridge",
	"Mega-Cart",
	"Behr Bonz",
	"Vic Flash Plugin",
	"UltiMem",
	"Final Expansion",
}};

/** Public functions **/

/**
 * Look up a C64 cartridge type.
 * @param type Cartridge type
 * @return Cartridge type name, or nullptr if not found.
 */
const char *lookup_C64_cart_type(uint16_t type)
{
	if (unlikely(type >= ARRAY_SIZE(CBM_C64_cart_type_offtbl))) {
		return nullptr;
	}

	const unsigned int offset = CBM_C64_cart_type_offtbl[type];
	return (likely(offset != 0) ? &CBM_C64_cart_type_strtbl[offset] : nullptr);
}

/**
 * Look up a VIC-20 cartridge type.
 * @param type Cartridge type
 * @return Cartridge type name, or nullptr if not found.
 */
const char *lookup_VIC20_cart_type(uint16_t type)
{
	if (unlikely(type >= crt_types_vic20.size())) {
		return nullptr;
	}
	return crt_types_vic20[type];
}

} }
