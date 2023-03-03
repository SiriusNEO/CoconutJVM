/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/misc.cc
 * \brief Implementation of misc.h
 * \author SiriusNEO
 */

#include "misc.h"

namespace coconut {

namespace utils {

void split(const std::string& originStr, char delim,
           std::vector<std::string>& ret) {
  for (int i = 0, j = 0; i < originStr.size();) {
    while (j < originStr.size() && originStr[j] != delim) ++j;
    ret.push_back(originStr.substr(i, j - i));
    while (j < originStr.size() && originStr[j] == delim) ++j;
    i = j;
  }
}

}  // namespace utils

}  // namespace coconut
