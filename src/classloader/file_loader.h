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

  std::string jreHome_;
  std::string classpath_;

  std::vector<FileEntry> libEntries_;
  std::vector<FileEntry> extEntries_;
  std::vector<FileEntry> entries_;

 public:
  /*!
   * \brief Default constructor.
   *
   * The file will be searched in the following three paths:
   * - {jreHome}/jre/
   * - {jreHome}/jre/ext/
   * - classpath
   *
   * \param jreHome The jreHome path of Java env.
   * \param classpath The classpath of JVM specified by user.
   */
  FileLoader(const std::string& jreHome, const std::string& classpath);

  /*!
   * \brief Load a single class file from a prepared file loader.
   * \param className The name of the class we want to load.
   * \param buf The byte pool we want to write the content to.
   * \return The total size of this class file (bytes). -1 if load failed.
   */
  int loadClassFileBytes(const std::string& className, BYTE* buf);

 private:
  void initEntriesByClasspath(const std::string& classpath);

  void unpackWildcardPath(std::vector<FileEntry>& fromEntries,
                          std::vector<FileEntry>& toEntries);
};

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_FILE_LOADER_H_
