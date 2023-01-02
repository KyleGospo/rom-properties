/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * CBMCart.hpp: Commodore ROM cartridge reader.                            *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "librpbase/RomData.hpp"

namespace LibRomData {

ROMDATA_DECL_BEGIN(CBMCart)
ROMDATA_DECL_METADATA()
ROMDATA_DECL_IMGSUPPORT()
ROMDATA_DECL_IMGEXT()
ROMDATA_DECL_END()

}
