/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/misc.h
 * \brief Collection of some utils implementation.
 * \author SiriusNEO
 */

#ifndef SRC_UTILS_MISC_H_
#define SRC_UTILS_MISC_H_

#include <string>
#include <vector>

namespace coconut {

namespace utils {

/*!
 * \brief Check a pointer of BaseClass whether it points to a SubClass. SubClass
 * must be a subclass of BaseClass.
 * \tparam SubClass The sub-class.
 * \tparam BaseClass The base class.
 * \param ptr pointer of the BaseClass.
 * \return True if the pointer indeed points to this SubClass.
 */
template <typename SubClass, typename BaseClass>
inline bool instanceof (const BaseClass* ptr) {
  return dynamic_cast<const SubClass*>(ptr) != nullptr;
}

/*!
 * \brief Split a string into several sub strings by the delimiter.
 * \param originStr The original string.
 * \param delim The delimiter character.
 * \param ret The vector to store the splitted strings.
 */
void split(const std::string& originStr, char delim,
           std::vector<std::string>& ret);

}  // namespace utils

}  // namespace coconut

#endif  // SRC_UTILS_MISC_H_
