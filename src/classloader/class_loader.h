/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/class_loader.h
 * \brief JVM class loader.
 * \author SiriusNEO
 */

#ifndef SRC_CLASSLOADER_CLASS_LOADER_H_
#define SRC_CLASSLOADER_CLASS_LOADER_H_

#include <unordered_map>

#include "../rtda/class.h"

namespace coconut {

namespace classloader {

class ClassLoader {
 public:
 private:
  std::unordered_map<std::string, rtda::Class> loaded_class_;
};

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_CLASS_LOADER_H_
