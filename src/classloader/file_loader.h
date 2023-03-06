/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/file_loader.h
 * \brief FileLoader, from local loading java class file ([]bytes) into memory.
 * \author SiriusNEO
 */

#ifndef SRC_CLASSLOADER_FILE_LOADER_H_
#define SRC_CLASSLOADER_FILE_LOADER_H_

#include "../utils/typedef.h"
#include "file_entry.h"

namespace coconut {

namespace classloader {

/*!
 * \brief FileLoader, from local loading java class file ([]bytes) into memory.
 *
 * It automatically parse and load files with some certain formats into memory
 * (bytes).
 * Current support file format: directory(folder), zip/jar.
 */
class FileLoader {
 private:
  static const int MAX_PATH_NUM = 10;
  static const char PATH_SEPARATOR = ':';

  std::vector<FileEntry> entries;

 public:
  /*!
   * \brief Default constructor.
   *
   * Because we usually have some environment settings saying JRE_PATH, here we
   * set a "prefix" to represent the root we start. So the file will be searched
   * in the path: prefix+path.
   *
   * \param prefix The prefix of the path, that is, the "jre path" of Java env.
   * \param path The path, that is, the "classpath" of JVM.
   */
  FileLoader(const std::string& prefix, const std::string& path);

  /*!
   * \brief Load a single class file from a prepared file loader.
   * \param className The name of the class we want to load.
   * \param buf The byte pool we want to write the content to.
   * \return The total size of this class file (bytes). -1 if load failed.
   */
  int loadClassFileBytes(const std::string& className, BYTE* buf);
};

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_FILE_LOADER_H_
