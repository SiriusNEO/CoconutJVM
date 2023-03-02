/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/cmdline.cc
 * \brief Implementation of cmdline.h
 * \author SiriusNEO
 */

#include "cmdline.h"

namespace coconut {

namespace utils {

CommandOptions::CommandOptions(int argc, char* argv[])
    : classPath(DEFAULT_CP), mainClassName(DEFAULT_MAINCN), args() {
  if (argc <= 1) {
    commandLinePanic("error: no argument.");
  }

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--help") == 0) {
      printf(
          "Usage: coconut [options] <mainclass> [args...] (to execute a "
          "class)\n\n");
      printf(
          "Arguments following the main class will be passed to main "
          "class.\n\n");
      printf("Options:\n");
      printf("\t--help\tshow the help documentation\n");
      printf("\t--version\tshow the version information\n");
      printf("\t--class-path\tclass search path\n");
      printf("\t--jre-path\tjava runtime environment path\n");
      exit(0);
    } else if (std::strcmp(argv[i], "--version") == 0) {
      printf("%s\n", VERSION);
      exit(0);
    } else if (std::strcmp(argv[i], "--class-path") == 0) {
      ++i;
      if (i == argc) {
        commandLinePanic(
            "error: --class-path requires class path specification");
      }
      classPath = std::string(argv[i]);
    } else if (std::strcmp(argv[i], "--jre-path") == 0) {
      ++i;
      if (i == argc) {
        commandLinePanic("error: --jre-path requires jre path specification");
      }
      jrePath = std::string(argv[i]);
    } else if (mainClassName == DEFAULT_MAINCN) {
      // this must be the main class
      mainClassName = std::string(argv[i]);
    } else {
      // args passed to main class
      args.push_back(std::string(argv[i]));
    }
  }
}

}  // namespace utils

}  // namespace coconut
