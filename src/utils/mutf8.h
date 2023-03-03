/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/mutf8.h
 * \brief Modified UTF8 converter (decoder).
 * References: https://github.com/sciencesakura/mutf-8/blob/master/src/index.ts
 * \author SiriusNEO
 */

#ifndef SRC_UTILS_MUTF8_H_
#define SRC_UTILS_MUTF8_H_

#include <utf16/converter.h>

#include <string>
#include <vector>

#include "logging.h"
#include "typedef.h"

namespace coconut {

namespace utils {

/*!
 * \brief Convert bytes to utf16 string.
 * \param bytes The bytes to be converted.
 * \param size The total size of bytes.
 * \return The converted utf16 string.
 */
std::string utf16fromBytes(utf16_t* bytes, size_t size);

/*!
 * \brief Raise mutf8 decode error.
 * \throw mutf8 decode error.
 */
void _decodeError();

/*!
 * \brief Decode mutf8 string from bytes.
 * \param bytesStream the vector of bytes to be decoded.
 * \throw mutf8 decode error.
 * \return The converted string.
 */
std::string decodeMUTF8FromBytes(const std::vector<BYTE>& bytesStream);

}  // namespace utils

}  // namespace coconut

#endif  // SRC_UTILS_MUTF8_H_
