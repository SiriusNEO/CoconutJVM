/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/cmdline.h
 * \brief The command line tool for coconut JVM.
 * \author SiriusNEO
 */

#ifndef SRC_UTILS_CMDLINE_H_
#define SRC_UTILS_CMDLINE_H_

#include "typedef.h"

namespace coconut {

namespace utils {

#define VERSION "coconut 0.1dev"

#define DEFAULT_CP "./"
#define DEFAULT_MAINCN "Main.class"
#define DEFAULT_JREPATH "./"

/*! \brief Error in command line. */
void commandLinePanic(const char* what);

/*!
 * \brief Wrapper for commandline options.
 *
 * When constructing, it will parse the command line inputs (argc, argv) into
 * the information we want.
 *
 * Note that we don't use the exceptions in utils/logging in command line,
 * because it's not a part of JVM.
 */
class CommandOptions {
 public:
  /*! \brief jre path. not a standard rule. */
  std::string jrePath;

  /*! \brief classpath. */
  std::string classPath;

  /*! \brief The name of the main class. */
  std::string mainClassName;

  /*! \brief Args passed to the main class. */
  Strings args;

  /*!
   * \brief Default constructor. Parse and wrap the command line.
   * \param argc The argument counter.
   * \param argv The argument values.
   */
  CommandOptions(int argc, char* argv[]);
};

}  // namespace utils

}  // namespace coconut

#endif  // SRC_UTILS_CMDLINE_H_
