/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/class_loader.cc
 * \brief Implementation of class_loader.h.
 * \author SiriusNEO
 */

#include "class_loader.h"

namespace coconut {

namespace classloader {

rtda::Class* ClassLoader::loadClass(std::string className) {
  auto it = loadedClass_.find(className);
  if (it != loadedClass_.end()) {
    return &it->second;
  }

  // read classfile data
  utils::ByteReader byteReader(MAX_CLASS_DATA_SIZE);
  int code = fileLoader_->loadClassFileBytes(className, byteReader.bytePool);
  CHECK(code != -1) << "java.lang.ClassFormatError";

  // define class
  rtda::Class newClass = std::move(this->defineClass(byteReader));

  // link class
  this->link(&newClass);

  // cache it and return
  loadedClass_.insert({className, newClass});
  it = loadedClass_.find(className);
  CHECK(it != loadedClass_.end()) << "Must can find";
  return &it->second;
}

rtda::Class ClassLoader::defineClass(utils::ByteReader& byteReader) {
  // parse into classfile
  classloader::ClassFile classFile(byteReader);

  // convert into Class
  rtda::Class newClass(classFile);

  // resolve super class
  if (!classFile.superClassName().empty()) {
    newClass.superClass = this->loadClass(classFile.superClassName());
  }

  // resolve interfaces
  for (int i = 0; i < static_cast<int>(classFile.interfaces.size()); ++i) {
    auto interfaceName = classFile.cp->getClassNameStr(classFile.interfaces[i]);
    newClass.interfaces.push_back(this->loadClass(interfaceName));
  }

  return newClass;
}

}  // namespace classloader
}  // namespace coconut
