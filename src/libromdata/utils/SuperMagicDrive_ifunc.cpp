/***************************************************************************
 * ROM Properties Page shell extension. (librpbase)                        *
 * SuperMagicDrive_ifunc.cpp: SuperMagicDrive IFUNC resolution functions.  *
 *                                                                         *
 * Copyright (c) 2016-2022 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#include "stdafx.h"
#include "config.librpbase.h"
#include "config.librpcpu.h"

#ifdef HAVE_IFUNC

#include "SuperMagicDrive.hpp"
using namespace LibRomData;

// NOTE: llvm/clang 14.0.0 fails to detect the resolver functions
// if they're marked static, even though the docs say this is okay.
// In C code, it merely warns that the resolvers aren't used, but
// in C++ code, the IFUNC_ATTR() attribute fails.

// IFUNC attribute doesn't support C++ name mangling.
extern "C" {

#ifndef SMD_ALWAYS_HAS_SSE2
/**
 * IFUNC resolver function for decodeBlock().
 * @return Function pointer.
 */
NO_SANITIZE_ADDRESS
__typeof__(&SuperMagicDrive::decodeBlock_cpp) decodeBlock_resolve(void)
{
	// NOTE: Since libromdata is a shared library now, IFUNC resolvers
	// cannot call PLT functions. Otherwise, it will crash.
	// We'll use gcc's built-in CPU ID functions instead.
	// Requires gcc-4.8 or later, or clang-6.0 or later.

#if defined(SMD_HAS_SSE2) || defined(SMD_HAS_MMX)
	__builtin_cpu_init();
#endif

#ifdef SMD_HAS_SSE2
	if (__builtin_cpu_supports("sse2")) {
		return &SuperMagicDrive::decodeBlock_sse2;
	} else
#endif /* SMD_HAS_SSE2 */
#ifdef SMD_HAS_MMX
	if (__builtin_cpu_supports("mmx")) {
		return &SuperMagicDrive::decodeBlock_mmx;
	} else
#endif /* SMD_HAS_MMX */
	{
		return &SuperMagicDrive::decodeBlock_cpp;
	}
}
#endif /* SMD_ALWAYS_HAS_SSE2 */

}

#ifndef SMD_ALWAYS_HAS_SSE2
void SuperMagicDrive::decodeBlock(uint8_t *RESTRICT pDest, const uint8_t *RESTRICT pSrc)
	IFUNC_ATTR(decodeBlock_resolve);
#endif /* SMD_ALWAYS_HAS_SSE2 */

#endif /* HAVE_IFUNC */
