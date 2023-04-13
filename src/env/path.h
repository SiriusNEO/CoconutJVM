/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/env/path.h
 * \brief Path environment config & auto searching.
 * \author SiriusNEO
 */

#ifndef SRC_ENV_PATH_H_
#define SRC_ENV_PATH_H_

#include <dirent.h>

#include "../utils/typedef.h"

namespace coconut {

namespace env {

std::string configJreHome(const std::string& jreHome) { return jreHome; }

std::string configClasspath(const std::string& classpath) { return classpath; }

}  // namespace env
}  // namespace coconut

#endif  // SRC_ENV_PATH_H_
