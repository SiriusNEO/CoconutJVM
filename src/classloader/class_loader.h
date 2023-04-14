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

#include "../rtda/heap/class.h"
#include "file_loader.h"

namespace coconut {

namespace classloader {

class ClassLoader {
 public:
  explicit ClassLoader(FileLoader* fileLoader) : fileLoader_(fileLoader) {}

  rtda::Class* loadClass(std::string className);

  rtda::Class defineClass(utils::ByteReader& byteReader);

  void link(rtda::Class* thisClass) {
    this->verifyClass(thisClass);
    this->prepareForClass(thisClass);
    // TODO: resolution
  }

 private:
  static const int MAX_CLASS_DATA_SIZE = 4 * 1024;  // 4 KB

  FileLoader* fileLoader_;
  std::unordered_map<std::string, rtda::Class> loadedClass_;

  void verifyClass(rtda::Class* thisClass) {
    // TODO: implement JVM verify algorithm
  }

  void prepareForClass(rtda::Class* thisClass) {}
};

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_CLASS_LOADER_H_
