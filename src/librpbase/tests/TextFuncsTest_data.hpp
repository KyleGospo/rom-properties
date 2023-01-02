/***************************************************************************
 * ROM Properties Page shell extension. (librpbase/tests)                  *
 * TextFuncsTest_data.hpp: Data for TextFuncsTest.                         *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

// NOTE: 8-bit test strings are unsigned in order to prevent
// narrowing conversion warnings from appearing.
// char16_t is defined as unsigned, so this isn't a problem
// for 16-bit strings.

/**
 * cp1252 test string.
 * Contains all possible cp1252 code points.
 * Does not include these unassigned code points:
 * - 0x81, 0x8D, 0x8F, 0x90, 0x9D
 * Also does not include 0x80 (Euro) because iconv
 * doesn't support that in cp1252.
 *
 * TODO: Re-add invalid code points and check that
 * they're converted to '?'.
 */
const uint8_t TextFuncsTest::cp1252_data[250] = {
	// NOTE: The NULL terminator is at the end,
	// not the beginning.
	     0x01,0x02,0x03,0x04,0x05,0x06,0x07,
	0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
	0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,
	0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
	0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,
	0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,
	0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,
	0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,
	0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
	          0x82,0x83,0x84,0x85,0x86,0x87,
	0x88,0x89,0x8A,0x8B,0x8C,     0x8E,
	     0x91,0x92,0x93,0x94,0x95,0x96,0x97,
	0x98,0x99,0x9A,0x9B,0x9C,     0x9E,0x9F,
	0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,
	0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
	0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,
	0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
	0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,
	0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
	0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,
	0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
	0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,
	0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
	0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,
	0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
	0x00
};

/**
 * cp1252 to UTF-8 test string.
 * Contains the expected result from:
 * - cp1252_to_utf8(cp1252_data, ARRAY_SIZE_I(cp1252_data))
 * - cp1252_sjis_to_utf8(cp1252_data, ARRAY_SIZE_I(cp1252_data))
 */
const uint8_t TextFuncsTest::cp1252_utf8_data[388] = {
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
	0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
	0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
	0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,
	0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
	0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,
	0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
	0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,
	0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,
	0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,
	0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,
	0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0xE2,
	0x80,0x9A,0xC6,0x92,0xE2,0x80,0x9E,0xE2,
	0x80,0xA6,0xE2,0x80,0xA0,0xE2,0x80,0xA1,
	0xCB,0x86,0xE2,0x80,0xB0,0xC5,0xA0,0xE2,
	0x80,0xB9,0xC5,0x92,0xC5,0xBD,0xE2,0x80,
	0x98,0xE2,0x80,0x99,0xE2,0x80,0x9C,0xE2,
	0x80,0x9D,0xE2,0x80,0xA2,0xE2,0x80,0x93,
	0xE2,0x80,0x94,0xCB,0x9C,0xE2,0x84,0xA2,
	0xC5,0xA1,0xE2,0x80,0xBA,0xC5,0x93,0xC5,
	0xBE,0xC5,0xB8,0xC2,0xA0,0xC2,0xA1,0xC2,
	0xA2,0xC2,0xA3,0xC2,0xA4,0xC2,0xA5,0xC2,
	0xA6,0xC2,0xA7,0xC2,0xA8,0xC2,0xA9,0xC2,
	0xAA,0xC2,0xAB,0xC2,0xAC,0xC2,0xAD,0xC2,
	0xAE,0xC2,0xAF,0xC2,0xB0,0xC2,0xB1,0xC2,
	0xB2,0xC2,0xB3,0xC2,0xB4,0xC2,0xB5,0xC2,
	0xB6,0xC2,0xB7,0xC2,0xB8,0xC2,0xB9,0xC2,
	0xBA,0xC2,0xBB,0xC2,0xBC,0xC2,0xBD,0xC2,
	0xBE,0xC2,0xBF,0xC3,0x80,0xC3,0x81,0xC3,
	0x82,0xC3,0x83,0xC3,0x84,0xC3,0x85,0xC3,
	0x86,0xC3,0x87,0xC3,0x88,0xC3,0x89,0xC3,
	0x8A,0xC3,0x8B,0xC3,0x8C,0xC3,0x8D,0xC3,
	0x8E,0xC3,0x8F,0xC3,0x90,0xC3,0x91,0xC3,
	0x92,0xC3,0x93,0xC3,0x94,0xC3,0x95,0xC3,
	0x96,0xC3,0x97,0xC3,0x98,0xC3,0x99,0xC3,
	0x9A,0xC3,0x9B,0xC3,0x9C,0xC3,0x9D,0xC3,
	0x9E,0xC3,0x9F,0xC3,0xA0,0xC3,0xA1,0xC3,
	0xA2,0xC3,0xA3,0xC3,0xA4,0xC3,0xA5,0xC3,
	0xA6,0xC3,0xA7,0xC3,0xA8,0xC3,0xA9,0xC3,
	0xAA,0xC3,0xAB,0xC3,0xAC,0xC3,0xAD,0xC3,
	0xAE,0xC3,0xAF,0xC3,0xB0,0xC3,0xB1,0xC3,
	0xB2,0xC3,0xB3,0xC3,0xB4,0xC3,0xB5,0xC3,
	0xB6,0xC3,0xB7,0xC3,0xB8,0xC3,0xB9,0xC3,
	0xBA,0xC3,0xBB,0xC3,0xBC,0xC3,0xBD,0xC3,
	0xBE,0xC3,0xBF,0x00
};

/**
 * cp1252 to UTF-16 test string.
 * Contains the expected result from:
 * - cp1252_to_utf16(cp1252_data, ARRAY_SIZE_I(cp1252_data))
 * - cp1252_sjis_to_utf16(cp1252_data, ARRAY_SIZE_I(cp1252_data))
 */
const char16_t TextFuncsTest::cp1252_utf16_data[250] =
{
	0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,
	0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,0x0010,
	0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,0x0017,0x0018,
	0x0019,0x001A,0x001B,0x001C,0x001D,0x001E,0x001F,0x0020,
	0x0021,0x0022,0x0023,0x0024,0x0025,0x0026,0x0027,0x0028,
	0x0029,0x002A,0x002B,0x002C,0x002D,0x002E,0x002F,0x0030,
	0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,
	0x0039,0x003A,0x003B,0x003C,0x003D,0x003E,0x003F,0x0040,
	0x0041,0x0042,0x0043,0x0044,0x0045,0x0046,0x0047,0x0048,
	0x0049,0x004A,0x004B,0x004C,0x004D,0x004E,0x004F,0x0050,
	0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,0x0058,
	0x0059,0x005A,0x005B,0x005C,0x005D,0x005E,0x005F,0x0060,
	0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067,0x0068,
	0x0069,0x006A,0x006B,0x006C,0x006D,0x006E,0x006F,0x0070,
	0x0071,0x0072,0x0073,0x0074,0x0075,0x0076,0x0077,0x0078,
	0x0079,0x007A,0x007B,0x007C,0x007D,0x007E,0x007F,0x201A,
	0x0192,0x201E,0x2026,0x2020,0x2021,0x02C6,0x2030,0x0160,
	0x2039,0x0152,0x017D,0x2018,0x2019,0x201C,0x201D,0x2022,
	0x2013,0x2014,0x02DC,0x2122,0x0161,0x203A,0x0153,0x017E,
	0x0178,0x00A0,0x00A1,0x00A2,0x00A3,0x00A4,0x00A5,0x00A6,
	0x00A7,0x00A8,0x00A9,0x00AA,0x00AB,0x00AC,0x00AD,0x00AE,
	0x00AF,0x00B0,0x00B1,0x00B2,0x00B3,0x00B4,0x00B5,0x00B6,
	0x00B7,0x00B8,0x00B9,0x00BA,0x00BB,0x00BC,0x00BD,0x00BE,
	0x00BF,0x00C0,0x00C1,0x00C2,0x00C3,0x00C4,0x00C5,0x00C6,
	0x00C7,0x00C8,0x00C9,0x00CA,0x00CB,0x00CC,0x00CD,0x00CE,
	0x00CF,0x00D0,0x00D1,0x00D2,0x00D3,0x00D4,0x00D5,0x00D6,
	0x00D7,0x00D8,0x00D9,0x00DA,0x00DB,0x00DC,0x00DD,0x00DE,
	0x00DF,0x00E0,0x00E1,0x00E2,0x00E3,0x00E4,0x00E5,0x00E6,
	0x00E7,0x00E8,0x00E9,0x00EA,0x00EB,0x00EC,0x00ED,0x00EE,
	0x00EF,0x00F0,0x00F1,0x00F2,0x00F3,0x00F4,0x00F5,0x00F6,
	0x00F7,0x00F8,0x00F9,0x00FA,0x00FB,0x00FC,0x00FD,0x00FE,
	0x00FF,0x0000
};

/**
 * Shift-JIS test string.
 *
 * TODO: Get a longer test string.
 * This string is from the JP Pokemon Colosseum (GCN) save file,
 * plus a wave dash character (8160).
 */
const uint8_t TextFuncsTest::sjis_data[36] = {
	0x83,0x7C,0x83,0x50,0x83,0x82,0x83,0x93,
	0x83,0x52,0x83,0x8D,0x83,0x56,0x83,0x41,
	0x83,0x80,0x0A,0x83,0x5A,0x81,0x5B,0x83,
	0x75,0x83,0x74,0x83,0x40,0x83,0x43,0x83,
	0x8B,0x81,0x60,0x00
};

/**
 * Shift-JIS to UTF-8 test string.
 * Contains the expected result from:
 * - cp1252_sjis_to_utf8(sjis_data, ARRAY_SIZE_I(sjis_data))
 */
const uint8_t TextFuncsTest::sjis_utf8_data[53] = {
	0xE3,0x83,0x9D,0xE3,0x82,0xB1,0xE3,0x83,
	0xA2,0xE3,0x83,0xB3,0xE3,0x82,0xB3,0xE3,
	0x83,0xAD,0xE3,0x82,0xB7,0xE3,0x82,0xA2,
	0xE3,0x83,0xA0,0x0A,0xE3,0x82,0xBB,0xE3,
	0x83,0xBC,0xE3,0x83,0x96,0xE3,0x83,0x95,
	0xE3,0x82,0xA1,0xE3,0x82,0xA4,0xE3,0x83,
	0xAB,0xEF,0xBD,0x9E,0x00
};

/**
 * Shift-JIS to UTF-16 test string.
 * Contains the expected result from:
 * - cp1252_sjis_to_utf16(sjis_data, ARRAY_SIZE_I(sjis_data))
 */
const char16_t TextFuncsTest::sjis_utf16_data[19] = {
    0x30DD, 0x30B1, 0x30E2, 0x30F3, 0x30B3, 0x30ED, 0x30B7, 0x30A2,
    0x30E0, 0x000A, 0x30BB, 0x30FC, 0x30D6, 0x30D5, 0x30A1, 0x30A4,
    0x30EB, 0xFF5E, 0x0000
};

/**
 * Shift-JIS test string with a cp1252 copyright symbol. (0xA9)
 * This string is incorrectly detected as Shift-JIS because
 * all bytes are valid.
 */
const uint8_t TextFuncsTest::sjis_copyright_in[16] = {
	0xA9,0x20,0x32,0x30,0x30,0x32,0x20,0x4E,
	0x69,0x6E,0x74,0x65,0x6E,0x64,0x6F,0x00
};

/**
 * UTF-8 result from:
 * - cp1252_sjis_to_utf8(sjis_copyright_in, sizeof(sjis_copyright_in))
 */
const uint8_t TextFuncsTest::sjis_copyright_out_utf8[18] = {
	0xEF,0xBD,0xA9,0x20,0x32,0x30,0x30,0x32,
	0x20,0x4E,0x69,0x6E,0x74,0x65,0x6E,0x64,
	0x6F,0x00
};

/**
 * UTF-16 result from:
 * - cp1252_sjis_to_utf16(sjis_copyright_in, sizeof(sjis_copyright_in))
 */
const char16_t TextFuncsTest::sjis_copyright_out_utf16[16] = {
	0xFF69,0x0020,0x0032,0x0030,0x0030,0x0032,0x0020,0x004E,
	0x0069,0x006E,0x0074,0x0065,0x006E,0x0064,0x006F,0x0000
};

/**
 * UTF-8 test string.
 * Contains Latin-1, BMP, and SMP characters.
 *
 * This contains the same string as
 * utf16le_data[] and utf16be_data[].
 */
const uint8_t TextFuncsTest::utf8_data[325] = {
	0x54,0x68,0x65,0x20,0x71,0x75,0x69,0x63,
	0x6B,0x20,0x62,0x72,0x6F,0x77,0x6E,0x20,
	0x66,0x6F,0x78,0x20,0x6A,0x75,0x6D,0x70,
	0x73,0x20,0x6F,0x76,0x65,0x72,0x20,0x74,
	0x68,0x65,0x20,0x6C,0x61,0x7A,0x79,0x20,
	0x64,0x6F,0x67,0x2E,0x0A,0x4D,0x69,0x73,
	0x63,0x65,0x6C,0x6C,0x61,0x6E,0x65,0x6F,
	0x75,0x73,0x20,0x63,0x75,0x72,0x72,0x65,
	0x6E,0x63,0x79,0x20,0x73,0x79,0x6D,0x62,
	0x6F,0x6C,0x73,0x3A,0x20,0x24,0xC2,0xA2,
	0xC2,0xA3,0xC2,0xA5,0x0A,0x48,0x65,0x72,
	0x65,0x2C,0x20,0x68,0x61,0x76,0x65,0x20,
	0x73,0x6F,0x6D,0x65,0x20,0x50,0x6F,0x6B,
	0xC3,0xA9,0x64,0x6F,0x6C,0x6C,0x61,0x72,
	0x73,0x3A,0x20,0xE2,0x82,0xBD,0x32,0x30,
	0x30,0x0A,0x4F,0x6C,0x64,0x20,0x63,0x70,
	0x34,0x33,0x37,0x20,0x62,0x6F,0x78,0x20,
	0x64,0x72,0x61,0x77,0x69,0x6E,0x67,0x20,
	0x63,0x68,0x61,0x72,0x61,0x63,0x74,0x65,
	0x72,0x73,0x3A,0x20,0xE2,0x96,0x91,0xE2,
	0x96,0x92,0xE2,0x96,0x93,0xE2,0x96,0x88,
	0x0A,0xE2,0x86,0x91,0xE2,0x86,0x91,0xE2,
	0x86,0x93,0xE2,0x86,0x93,0xE2,0x86,0x90,
	0xE2,0x86,0x92,0xE2,0x86,0x90,0xE2,0x86,
	0x92,0xE2,0x92,0xB7,0xE2,0x92,0xB6,0x28,
	0x73,0x74,0x61,0x72,0x74,0x29,0x0A,0x0A,
	0x41,0x6E,0x64,0x20,0x66,0x69,0x6E,0x61,
	0x6C,0x6C,0x79,0x2C,0x20,0x73,0x6F,0x6D,
	0x65,0x20,0x53,0x75,0x70,0x70,0x6C,0x65,
	0x6D,0x65,0x6E,0x74,0x61,0x72,0x79,0x20,
	0x4D,0x75,0x6C,0x74,0x69,0x6C,0x69,0x6E,
	0x67,0x75,0x61,0x6C,0x20,0x50,0x6C,0x61,
	0x6E,0x65,0x20,0x63,0x68,0x61,0x72,0x61,
	0x63,0x74,0x65,0x72,0x73,0x3A,0x0A,0xF0,
	0x9F,0x8D,0x8C,0xF0,0x9F,0x8D,0x99,0xF0,
	0x9F,0x8D,0xA9,0xF0,0x9F,0x92,0xB5,0xF0,
	0x9F,0x92,0xBE,0x20,0x2E,0x2E,0x2E,0x20,
	0xF0,0x9F,0x94,0x9C,0x0A,0x0A,0x54,0x68,
	0x61,0x74,0x27,0x73,0x20,0x61,0x6C,0x6C,
	0x20,0x66,0x6F,0x72,0x20,0x6E,0x6F,0x77,
	0x2E,0x2E,0x2E,0x0A,0x00
};

/**
 * UTF-16LE test string.
 * Contains Latin-1, BMP, and SMP characters.
 *
 * This contains the same string as
 * utf8_data[] and utf16be_data[].
 *
 * NOTE: This is encoded as uint8_t to prevent
 * byteswapping issues.
 */
const uint8_t TextFuncsTest::utf16le_data[558] = {
	0x54,0x00,0x68,0x00,0x65,0x00,0x20,0x00,
	0x71,0x00,0x75,0x00,0x69,0x00,0x63,0x00,
	0x6B,0x00,0x20,0x00,0x62,0x00,0x72,0x00,
	0x6F,0x00,0x77,0x00,0x6E,0x00,0x20,0x00,
	0x66,0x00,0x6F,0x00,0x78,0x00,0x20,0x00,
	0x6A,0x00,0x75,0x00,0x6D,0x00,0x70,0x00,
	0x73,0x00,0x20,0x00,0x6F,0x00,0x76,0x00,
	0x65,0x00,0x72,0x00,0x20,0x00,0x74,0x00,
	0x68,0x00,0x65,0x00,0x20,0x00,0x6C,0x00,
	0x61,0x00,0x7A,0x00,0x79,0x00,0x20,0x00,
	0x64,0x00,0x6F,0x00,0x67,0x00,0x2E,0x00,
	0x0A,0x00,0x4D,0x00,0x69,0x00,0x73,0x00,
	0x63,0x00,0x65,0x00,0x6C,0x00,0x6C,0x00,
	0x61,0x00,0x6E,0x00,0x65,0x00,0x6F,0x00,
	0x75,0x00,0x73,0x00,0x20,0x00,0x63,0x00,
	0x75,0x00,0x72,0x00,0x72,0x00,0x65,0x00,
	0x6E,0x00,0x63,0x00,0x79,0x00,0x20,0x00,
	0x73,0x00,0x79,0x00,0x6D,0x00,0x62,0x00,
	0x6F,0x00,0x6C,0x00,0x73,0x00,0x3A,0x00,
	0x20,0x00,0x24,0x00,0xA2,0x00,0xA3,0x00,
	0xA5,0x00,0x0A,0x00,0x48,0x00,0x65,0x00,
	0x72,0x00,0x65,0x00,0x2C,0x00,0x20,0x00,
	0x68,0x00,0x61,0x00,0x76,0x00,0x65,0x00,
	0x20,0x00,0x73,0x00,0x6F,0x00,0x6D,0x00,
	0x65,0x00,0x20,0x00,0x50,0x00,0x6F,0x00,
	0x6B,0x00,0xE9,0x00,0x64,0x00,0x6F,0x00,
	0x6C,0x00,0x6C,0x00,0x61,0x00,0x72,0x00,
	0x73,0x00,0x3A,0x00,0x20,0x00,0xBD,0x20,
	0x32,0x00,0x30,0x00,0x30,0x00,0x0A,0x00,
	0x4F,0x00,0x6C,0x00,0x64,0x00,0x20,0x00,
	0x63,0x00,0x70,0x00,0x34,0x00,0x33,0x00,
	0x37,0x00,0x20,0x00,0x62,0x00,0x6F,0x00,
	0x78,0x00,0x20,0x00,0x64,0x00,0x72,0x00,
	0x61,0x00,0x77,0x00,0x69,0x00,0x6E,0x00,
	0x67,0x00,0x20,0x00,0x63,0x00,0x68,0x00,
	0x61,0x00,0x72,0x00,0x61,0x00,0x63,0x00,
	0x74,0x00,0x65,0x00,0x72,0x00,0x73,0x00,
	0x3A,0x00,0x20,0x00,0x91,0x25,0x92,0x25,
	0x93,0x25,0x88,0x25,0x0A,0x00,0x91,0x21,
	0x91,0x21,0x93,0x21,0x93,0x21,0x90,0x21,
	0x92,0x21,0x90,0x21,0x92,0x21,0xB7,0x24,
	0xB6,0x24,0x28,0x00,0x73,0x00,0x74,0x00,
	0x61,0x00,0x72,0x00,0x74,0x00,0x29,0x00,
	0x0A,0x00,0x0A,0x00,0x41,0x00,0x6E,0x00,
	0x64,0x00,0x20,0x00,0x66,0x00,0x69,0x00,
	0x6E,0x00,0x61,0x00,0x6C,0x00,0x6C,0x00,
	0x79,0x00,0x2C,0x00,0x20,0x00,0x73,0x00,
	0x6F,0x00,0x6D,0x00,0x65,0x00,0x20,0x00,
	0x53,0x00,0x75,0x00,0x70,0x00,0x70,0x00,
	0x6C,0x00,0x65,0x00,0x6D,0x00,0x65,0x00,
	0x6E,0x00,0x74,0x00,0x61,0x00,0x72,0x00,
	0x79,0x00,0x20,0x00,0x4D,0x00,0x75,0x00,
	0x6C,0x00,0x74,0x00,0x69,0x00,0x6C,0x00,
	0x69,0x00,0x6E,0x00,0x67,0x00,0x75,0x00,
	0x61,0x00,0x6C,0x00,0x20,0x00,0x50,0x00,
	0x6C,0x00,0x61,0x00,0x6E,0x00,0x65,0x00,
	0x20,0x00,0x63,0x00,0x68,0x00,0x61,0x00,
	0x72,0x00,0x61,0x00,0x63,0x00,0x74,0x00,
	0x65,0x00,0x72,0x00,0x73,0x00,0x3A,0x00,
	0x0A,0x00,0x3C,0xD8,0x4C,0xDF,0x3C,0xD8,
	0x59,0xDF,0x3C,0xD8,0x69,0xDF,0x3D,0xD8,
	0xB5,0xDC,0x3D,0xD8,0xBE,0xDC,0x20,0x00,
	0x2E,0x00,0x2E,0x00,0x2E,0x00,0x20,0x00,
	0x3D,0xD8,0x1C,0xDD,0x0A,0x00,0x0A,0x00,
	0x54,0x00,0x68,0x00,0x61,0x00,0x74,0x00,
	0x27,0x00,0x73,0x00,0x20,0x00,0x61,0x00,
	0x6C,0x00,0x6C,0x00,0x20,0x00,0x66,0x00,
	0x6F,0x00,0x72,0x00,0x20,0x00,0x6E,0x00,
	0x6F,0x00,0x77,0x00,0x2E,0x00,0x2E,0x00,
	0x2E,0x00,0x0A,0x00,0x00,0x00
};

/**
 * UTF-16BE test string.
 * Contains Latin-1, BMP, and SMP characters.
 *
 * This contains the same string as
 * utf8_data[] and utf16le_data[].
 *
 * NOTE: This is encoded as uint8_t to prevent
 * byteswapping issues.
 */
const uint8_t TextFuncsTest::utf16be_data[558] = {
	0x00,0x54,0x00,0x68,0x00,0x65,0x00,0x20,
	0x00,0x71,0x00,0x75,0x00,0x69,0x00,0x63,
	0x00,0x6B,0x00,0x20,0x00,0x62,0x00,0x72,
	0x00,0x6F,0x00,0x77,0x00,0x6E,0x00,0x20,
	0x00,0x66,0x00,0x6F,0x00,0x78,0x00,0x20,
	0x00,0x6A,0x00,0x75,0x00,0x6D,0x00,0x70,
	0x00,0x73,0x00,0x20,0x00,0x6F,0x00,0x76,
	0x00,0x65,0x00,0x72,0x00,0x20,0x00,0x74,
	0x00,0x68,0x00,0x65,0x00,0x20,0x00,0x6C,
	0x00,0x61,0x00,0x7A,0x00,0x79,0x00,0x20,
	0x00,0x64,0x00,0x6F,0x00,0x67,0x00,0x2E,
	0x00,0x0A,0x00,0x4D,0x00,0x69,0x00,0x73,
	0x00,0x63,0x00,0x65,0x00,0x6C,0x00,0x6C,
	0x00,0x61,0x00,0x6E,0x00,0x65,0x00,0x6F,
	0x00,0x75,0x00,0x73,0x00,0x20,0x00,0x63,
	0x00,0x75,0x00,0x72,0x00,0x72,0x00,0x65,
	0x00,0x6E,0x00,0x63,0x00,0x79,0x00,0x20,
	0x00,0x73,0x00,0x79,0x00,0x6D,0x00,0x62,
	0x00,0x6F,0x00,0x6C,0x00,0x73,0x00,0x3A,
	0x00,0x20,0x00,0x24,0x00,0xA2,0x00,0xA3,
	0x00,0xA5,0x00,0x0A,0x00,0x48,0x00,0x65,
	0x00,0x72,0x00,0x65,0x00,0x2C,0x00,0x20,
	0x00,0x68,0x00,0x61,0x00,0x76,0x00,0x65,
	0x00,0x20,0x00,0x73,0x00,0x6F,0x00,0x6D,
	0x00,0x65,0x00,0x20,0x00,0x50,0x00,0x6F,
	0x00,0x6B,0x00,0xE9,0x00,0x64,0x00,0x6F,
	0x00,0x6C,0x00,0x6C,0x00,0x61,0x00,0x72,
	0x00,0x73,0x00,0x3A,0x00,0x20,0x20,0xBD,
	0x00,0x32,0x00,0x30,0x00,0x30,0x00,0x0A,
	0x00,0x4F,0x00,0x6C,0x00,0x64,0x00,0x20,
	0x00,0x63,0x00,0x70,0x00,0x34,0x00,0x33,
	0x00,0x37,0x00,0x20,0x00,0x62,0x00,0x6F,
	0x00,0x78,0x00,0x20,0x00,0x64,0x00,0x72,
	0x00,0x61,0x00,0x77,0x00,0x69,0x00,0x6E,
	0x00,0x67,0x00,0x20,0x00,0x63,0x00,0x68,
	0x00,0x61,0x00,0x72,0x00,0x61,0x00,0x63,
	0x00,0x74,0x00,0x65,0x00,0x72,0x00,0x73,
	0x00,0x3A,0x00,0x20,0x25,0x91,0x25,0x92,
	0x25,0x93,0x25,0x88,0x00,0x0A,0x21,0x91,
	0x21,0x91,0x21,0x93,0x21,0x93,0x21,0x90,
	0x21,0x92,0x21,0x90,0x21,0x92,0x24,0xB7,
	0x24,0xB6,0x00,0x28,0x00,0x73,0x00,0x74,
	0x00,0x61,0x00,0x72,0x00,0x74,0x00,0x29,
	0x00,0x0A,0x00,0x0A,0x00,0x41,0x00,0x6E,
	0x00,0x64,0x00,0x20,0x00,0x66,0x00,0x69,
	0x00,0x6E,0x00,0x61,0x00,0x6C,0x00,0x6C,
	0x00,0x79,0x00,0x2C,0x00,0x20,0x00,0x73,
	0x00,0x6F,0x00,0x6D,0x00,0x65,0x00,0x20,
	0x00,0x53,0x00,0x75,0x00,0x70,0x00,0x70,
	0x00,0x6C,0x00,0x65,0x00,0x6D,0x00,0x65,
	0x00,0x6E,0x00,0x74,0x00,0x61,0x00,0x72,
	0x00,0x79,0x00,0x20,0x00,0x4D,0x00,0x75,
	0x00,0x6C,0x00,0x74,0x00,0x69,0x00,0x6C,
	0x00,0x69,0x00,0x6E,0x00,0x67,0x00,0x75,
	0x00,0x61,0x00,0x6C,0x00,0x20,0x00,0x50,
	0x00,0x6C,0x00,0x61,0x00,0x6E,0x00,0x65,
	0x00,0x20,0x00,0x63,0x00,0x68,0x00,0x61,
	0x00,0x72,0x00,0x61,0x00,0x63,0x00,0x74,
	0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x3A,
	0x00,0x0A,0xD8,0x3C,0xDF,0x4C,0xD8,0x3C,
	0xDF,0x59,0xD8,0x3C,0xDF,0x69,0xD8,0x3D,
	0xDC,0xB5,0xD8,0x3D,0xDC,0xBE,0x00,0x20,
	0x00,0x2E,0x00,0x2E,0x00,0x2E,0x00,0x20,
	0xD8,0x3D,0xDD,0x1C,0x00,0x0A,0x00,0x0A,
	0x00,0x54,0x00,0x68,0x00,0x61,0x00,0x74,
	0x00,0x27,0x00,0x73,0x00,0x20,0x00,0x61,
	0x00,0x6C,0x00,0x6C,0x00,0x20,0x00,0x66,
	0x00,0x6F,0x00,0x72,0x00,0x20,0x00,0x6E,
	0x00,0x6F,0x00,0x77,0x00,0x2E,0x00,0x2E,
	0x00,0x2E,0x00,0x0A,0x00,0x00
};

#define U8_FFFD 0xEF,0xBF,0xBD
/**
 * Latin-1 to UTF-8 test string.
 * Contains the expected result from:
 * - latin1_to_utf8(cp1252_data, ARRAY_SIZE_I(cp1252_data))
 *
 * This includes the C1 control codes, as per the Unicode Latin-1 Supplement:
 * https://en.wikipedia.org/wiki/Latin-1_Supplement_(Unicode_block)
 */
const uint8_t TextFuncsTest::latin1_utf8_data[371+1] = {
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
	0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
	0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,
	0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
	0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,
	0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
	0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,
	0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
	0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,
	0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,
	0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70,
	0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,
	0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0xC2,
	0x82,0xC2,0x83,0xC2,0x84,0xC2,0x85,0xC2,
	0x86,0xC2,0x87,0xC2,0x88,0xC2,0x89,0xC2,
	0x8A,0xC2,0x8B,0xC2,0x8C,0xC2,0x8E,0xC2,
	0x91,0xC2,0x92,0xC2,0x93,0xC2,0x94,0xC2,
	0x95,0xC2,0x96,0xC2,0x97,0xC2,0x98,0xC2,
	0x99,0xC2,0x9A,0xC2,0x9B,0xC2,0x9C,0xC2,
	0x9E,0xC2,0x9F,0xC2,0xA0,0xC2,0xA1,0xC2,
	0xA2,0xC2,0xA3,0xC2,0xA4,0xC2,0xA5,0xC2,
	0xA6,0xC2,0xA7,0xC2,0xA8,0xC2,0xA9,0xC2,
	0xAA,0xC2,0xAB,0xC2,0xAC,0xC2,0xAD,0xC2,
	0xAE,0xC2,0xAF,0xC2,0xB0,0xC2,0xB1,0xC2,
	0xB2,0xC2,0xB3,0xC2,0xB4,0xC2,0xB5,0xC2,
	0xB6,0xC2,0xB7,0xC2,0xB8,0xC2,0xB9,0xC2,
	0xBA,0xC2,0xBB,0xC2,0xBC,0xC2,0xBD,0xC2,
	0xBE,0xC2,0xBF,0xC3,0x80,0xC3,0x81,0xC3,
	0x82,0xC3,0x83,0xC3,0x84,0xC3,0x85,0xC3,
	0x86,0xC3,0x87,0xC3,0x88,0xC3,0x89,0xC3,
	0x8A,0xC3,0x8B,0xC3,0x8C,0xC3,0x8D,0xC3,
	0x8E,0xC3,0x8F,0xC3,0x90,0xC3,0x91,0xC3,
	0x92,0xC3,0x93,0xC3,0x94,0xC3,0x95,0xC3,
	0x96,0xC3,0x97,0xC3,0x98,0xC3,0x99,0xC3,
	0x9A,0xC3,0x9B,0xC3,0x9C,0xC3,0x9D,0xC3,
	0x9E,0xC3,0x9F,0xC3,0xA0,0xC3,0xA1,0xC3,
	0xA2,0xC3,0xA3,0xC3,0xA4,0xC3,0xA5,0xC3,
	0xA6,0xC3,0xA7,0xC3,0xA8,0xC3,0xA9,0xC3,
	0xAA,0xC3,0xAB,0xC3,0xAC,0xC3,0xAD,0xC3,
	0xAE,0xC3,0xAF,0xC3,0xB0,0xC3,0xB1,0xC3,
	0xB2,0xC3,0xB3,0xC3,0xB4,0xC3,0xB5,0xC3,
	0xB6,0xC3,0xB7,0xC3,0xB8,0xC3,0xB9,0xC3,
	0xBA,0xC3,0xBB,0xC3,0xBC,0xC3,0xBD,0xC3,
	0xBE,0xC3,0xBF,0x00
};

/**
 * Latin-1 to UTF-16 test string.
 * Contains the expected result from:
 * - latin1_to_utf16(cp1252_data, ARRAY_SIZE_I(cp1252_data))
 *
 * This includes the C1 control codes, as per the Unicode Latin-1 Supplement:
 * https://en.wikipedia.org/wiki/Latin-1_Supplement_(Unicode_block)
 */
const char16_t TextFuncsTest::latin1_utf16_data[249+1] =
{
	0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,
	0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,0x0010,
	0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,0x0017,0x0018,
	0x0019,0x001A,0x001B,0x001C,0x001D,0x001E,0x001F,0x0020,
	0x0021,0x0022,0x0023,0x0024,0x0025,0x0026,0x0027,0x0028,
	0x0029,0x002A,0x002B,0x002C,0x002D,0x002E,0x002F,0x0030,
	0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,
	0x0039,0x003A,0x003B,0x003C,0x003D,0x003E,0x003F,0x0040,
	0x0041,0x0042,0x0043,0x0044,0x0045,0x0046,0x0047,0x0048,
	0x0049,0x004A,0x004B,0x004C,0x004D,0x004E,0x004F,0x0050,
	0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,0x0058,
	0x0059,0x005A,0x005B,0x005C,0x005D,0x005E,0x005F,0x0060,
	0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067,0x0068,
	0x0069,0x006A,0x006B,0x006C,0x006D,0x006E,0x006F,0x0070,
	0x0071,0x0072,0x0073,0x0074,0x0075,0x0076,0x0077,0x0078,
	0x0079,0x007A,0x007B,0x007C,0x007D,0x007E,0x007F,0x0082,
	0x0083,0x0084,0x0085,0x0086,0x0087,0x0088,0x0089,0x008A,
	0x008B,0x008C,0x008E,0x0091,0x0092,0x0093,0x0094,0x0095,
	0x0096,0x0097,0x0098,0x0099,0x009A,0x009B,0x009C,0x009E,
	0x009F,0x00A0,0x00A1,0x00A2,0x00A3,0x00A4,0x00A5,0x00A6,
	0x00A7,0x00A8,0x00A9,0x00AA,0x00AB,0x00AC,0x00AD,0x00AE,
	0x00AF,0x00B0,0x00B1,0x00B2,0x00B3,0x00B4,0x00B5,0x00B6,
	0x00B7,0x00B8,0x00B9,0x00BA,0x00BB,0x00BC,0x00BD,0x00BE,
	0x00BF,0x00C0,0x00C1,0x00C2,0x00C3,0x00C4,0x00C5,0x00C6,
	0x00C7,0x00C8,0x00C9,0x00CA,0x00CB,0x00CC,0x00CD,0x00CE,
	0x00CF,0x00D0,0x00D1,0x00D2,0x00D3,0x00D4,0x00D5,0x00D6,
	0x00D7,0x00D8,0x00D9,0x00DA,0x00DB,0x00DC,0x00DD,0x00DE,
	0x00DF,0x00E0,0x00E1,0x00E2,0x00E3,0x00E4,0x00E5,0x00E6,
	0x00E7,0x00E8,0x00E9,0x00EA,0x00EB,0x00EC,0x00ED,0x00EE,
	0x00EF,0x00F0,0x00F1,0x00F2,0x00F3,0x00F4,0x00F5,0x00F6,
	0x00F7,0x00F8,0x00F9,0x00FA,0x00FB,0x00FC,0x00FD,0x00FE,
	0x00FF,0x0000
};

/** Specialized code page functions. **/

/**
 * Atari ST to UTF-8 test string.
 * Contains all Atari ST characters that can be converted to Unicode.
 */
const char TextFuncsTest::atariST_data[236+1] =
	// 0x00
	"\x01\x02\x03\x04\x05\x08\n\x0B\x0C\r\x1A\x1B"
	// 0x20
	" !\"#$%&'()*+,-./0123456789:;<=>?"
	// 0x40
	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
	// 0x60
	"`abcdefghijklmnopqrstuvwxyz{|}~\x7F"
	// 0x80
	"\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"
	// 0x90
	"\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"
	// 0xA0
	"\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"
	// 0xB0
	"\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"
	// 0xC0
	"\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
	// 0xD0
	"\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
	// 0xE0
	"\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
	// 0xF0
	"\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

/**
 * Atari ST to UTF-16 test string.
 * Contains the expected result from:
 * - utf8_to_utf16(atariST_to_utf8(atariST_data, ARRAY_SIZE_I(atariST_data)))
 */
const char16_t TextFuncsTest::atariST_utf16_data[236+1] =
{
	0x21E7, 0x21E9, 0x21E8, 0x21E6, 0x274E, 0x2713, '\n', 0x266A, 0x240C, '\r', 0x0259, 0x241B,
	// 0x20
	' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	// 0x30
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
	// 0x40
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	// 0x50
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
	// 0x60
	'`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	// 0x70
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 0x2302,
	// 0x80
	0x00C7, 0x00FC, 0x00E9, 0x00E2, 0x00E4, 0x00E0, 0x00E5, 0x00E7,
	0x00EA, 0x00EB, 0x00E8, 0x00EF, 0x00EE, 0x00EC, 0x00C4, 0x00C5,
	// 0x90
	0x00C9, 0x00E6, 0x00C6, 0x00F4, 0x00F6, 0x00F2, 0x00FB, 0x00F9,
	0x00FF, 0x00D6, 0x00DC, 0x00A2, 0x00A3, 0x00A5, 0x00DF, 0x0192,
	// 0xA0
	0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00F1, 0x00D1, 0x00AA, 0x00BA,
	0x00BF, 0x2310, 0x00AC, 0x00BD, 0x00BC, 0x00A1, 0x00AB, 0x00BB,
	// 0xB0
	0x00E3, 0x00F5, 0x00D8, 0x00F8, 0x0153, 0x0152, 0x00C0, 0x00C3,
	0x00D5, 0x00A8, 0x00B4, 0x2020, 0x00B6, 0x00A9, 0x00AE, 0x2122,
	// 0xC0
	0x0133, 0x0132, 0x05D0, 0x05D1, 0x05D2, 0x05D3, 0x05D4, 0x05D5,
	0x05D6, 0x05D7, 0x05D8, 0x05D9, 0x05DB, 0x05DC, 0x05DE, 0x05E0,
	// 0xD0
	0x05E1, 0x05E2, 0x05E4, 0x05E6, 0x05E7, 0x05E8, 0x05E9, 0x05EA,
	0x05DF, 0x05DA, 0x05DD, 0x05E3, 0x05E5, 0x00A7, 0x2227, 0x221E,
	// 0xE0
	0x03B1, 0x03B2, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4,
	0x03A6, 0x0398, 0x03A9, 0x03B4, 0x222E, 0x03D5, 0x2208, 0x2229,
	// 0xF0
	0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248,
	0x00B0, 0x2022, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x00B3, 0x00AF,

	0
};

/**
 * Atari ATASCII to UTF-8 test string.
 * Contains all Atari ATASCII characters that can be converted to Unicode.
 */
const char TextFuncsTest::atascii_data[229+1] =
	// 0x00
	// NOTE: This string starts with a NULL...
	"\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
	// 0x10
	"\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
	// 0x20
	" !\"#$%&'()*+,-./0123456789:;<=>?"
	// 0x40
	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
	// 0x60
	"\x60" "abcdefghijklmnopqrstuvwxyz\x7B|\x7D\x7E\x7F"

	// 0x80
	"\x82\x88\x89\x8A\x8B\x8C\x8D\x8F\x95\x99\x9B"
	// 0xA0
	"\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"
	// 0xB0
	"\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"
	// 0xC0
	"\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
	// 0xD0
	"\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
	// 0xE0
	"\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
	// 0xF0
	"\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA";

/**
 * Atari ATASCII to UTF-16 test string.
 * Contains the expected result from:
 * - utf8_to_utf16(atascii_to_utf8(atascii_data, ARRAY_SIZE_I(atascii_data)-1))
 */
const char16_t TextFuncsTest::atascii_utf16_data[229+1] =
{
	// 0x00
	0x2665, 0x251C, 0x2590, 0x2518, 0x2524, 0x2510, 0x2571, 0x2572,
	0x25E2, 0x2597, 0x25E3, 0x259D, 0x2598, 0x2580, 0x2582, 0x2596,
	// 0x10
	0x2663, 0x250C, 0x2500, 0x253C, 0x25CF, 0x2584, 0x258E, 0x252C,
	0x2534, 0x258C, 0x2514, 0x001B, 0x2191, 0x2193, 0x2190, 0x2192,
	// 0x20
	' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	// 0x30
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
	// 0x40
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	// 0x50
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
	// 0x60
	0x2666, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	// 0x70
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0x2660, '|', 0x21B0, 0x25C0, 0x25B6,

	// 0x80
	0x258A, 0x25E4, 0x259B, 0x25E5, 0x2599, 0x259F, 0x2586, 0x259C, 0x2580, 0x2590, '\n',
	// 0xA0
	0x2588, '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	// 0xB0
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
	// 0xC0
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	// 0xD0
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
	// 0xE0
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
	// 0xF0
	'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

	0
};
