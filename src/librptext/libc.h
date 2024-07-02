/***************************************************************************
 * ROM Properties Page shell extension. (librptext)                        *
 * libc.h: Reimplementations of libc functions that aren't present on      *
 * this system.                                                            *
 *                                                                         *
 * Copyright (c) 2009-2024 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "config.librptext.h"
#include "common.h"

// C includes
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_STRNLEN
/**
 * String length with limit. (8-bit strings)
 * @param str The string itself
 * @param maxlen Maximum length of the string
 * @returns equivivalent to min(strlen(str), maxlen) without buffer overruns
 */
ATTR_ACCESS_SIZE(read_only, 1, 2)
size_t rp_strnlen(const char *str, size_t maxlen);

#  ifdef strnlen
#    undef strnlen
#  endif
#  define strnlen(str, maxlen) rp_strnlen((str), (maxlen))
#endif /* !HAVE_STRNLEN */

#ifndef HAVE_MEMMEM
/**
 * Find a string within a block of memory.
 * @param haystack Block of memory.
 * @param haystacklen Length of haystack.
 * @param needle String to search for.
 * @param needlelen Length of needle.
 * @return Location of needle in haystack, or NULL if not found.
 */
ATTR_ACCESS_SIZE(read_only, 1, 2)
ATTR_ACCESS_SIZE(read_only, 3, 4)
void *rp_memmem(const void *haystack, size_t haystacklen,
	        const void *needle, size_t needlelen);

#  ifdef memmem
#    undef memmem
#  endif
#  define memmem(haystack, haystacklen, needle, needlelen) rp_memmem((haystack), (haystacklen), (needle), (needlelen))
#endif /* !HAVE_MEMMEM */

#ifndef HAVE_STRLCAT
/**
 * strcat() but with a length parameter to prevent buffer overflows.
 * @param dst [in,out] Destination string
 * @param src [in] Source string
 * @param size [in] Size of destination string
 * @return Total length of the string that was attempted to be created: strlen(dst) + strlen(src)
 */
size_t rp_strlcat(char *dst, const char *src, size_t size);

#  ifdef strlcat
#    undef strlcat
#  endif
#  define strlcat(dst, src, size) rp_strlcat((dst), (src), (size))
#endif /* !HAVE_STRLCAT */

#ifdef __cplusplus
}
#endif
