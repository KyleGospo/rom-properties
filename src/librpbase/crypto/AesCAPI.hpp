/***************************************************************************
 * ROM Properties Page shell extension. (librpbase)                        *
 * AesCAPI.hpp: AES decryption class using Win32 CryptoAPI.                *
 *                                                                         *
 * Copyright (c) 2016-2023 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#pragma once

#include "IAesCipher.hpp"

namespace LibRpBase {

class AesCAPIPrivate;
class AesCAPI final : public IAesCipher
{
	public:
		AesCAPI();
		~AesCAPI() final;

	private:
		typedef IAesCipher super;
		RP_DISABLE_COPY(AesCAPI)
	private:
		friend class AesCAPIPrivate;
		AesCAPIPrivate *const d_ptr;

	public:
		/**
		 * Get the name of the AesCipher implementation.
		 * @return Name.
		 */
		const char *name(void) const final;

		/**
		 * Has the cipher been initialized properly?
		 * @return True if initialized; false if not.
		 */
		bool isInit(void) const final;

		/**
		 * Set the encryption key.
		 * @param pKey	[in] Key data.
		 * @param size	[in] Size of pKey, in bytes.
		 * @return 0 on success; negative POSIX error code on error.
		 */
		ATTR_ACCESS_SIZE(read_only, 2, 3)
		int setKey(const uint8_t *RESTRICT pKey, size_t size) final;

		/**
		 * Set the cipher chaining mode.
		 *
		 * Note that the IV/counter must be set *after* setting
		 * the chaining mode; otherwise, setIV() will fail.
		 *
		 * @param mode Cipher chaining mode.
		 * @return 0 on success; negative POSIX error code on error.
		 */
		int setChainingMode(ChainingMode mode) final;

		/**
		 * Set the IV (CBC mode) or counter (CTR mode).
		 * @param pIV	[in] IV/counter data.
		 * @param size	[in] Size of pIV, in bytes.
		 * @return 0 on success; negative POSIX error code on error.
		 */
		ATTR_ACCESS_SIZE(read_only, 2, 3)
		int setIV(const uint8_t *RESTRICT pIV, size_t size) final;

		/**
		 * Decrypt a block of data.
		 * Key and IV/counter must be set before calling this function.
		 *
		 * @param pData	[in/out] Data block.
		 * @param size	[in] Length of data block. (Must be a multiple of 16.)
		 * @return Number of bytes decrypted on success; 0 on error.
		 */
		ATTR_ACCESS_SIZE(read_write, 2, 3)
		size_t decrypt(uint8_t *RESTRICT pData, size_t size) final;
};

}
