/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classfile/file_loader.h
 * \brief FileLoader, from local loading java class file ([]bytes) into memory.
 * \author SiriusNEO
 */

#ifndef SRC_CLASSFILE_FILE_LOADER_H_
#define SRC_CLASSFILE_FILE_LOADER_H_

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zip/zip.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../utils/logging.h"
#include "../utils/misc.h"
#include "../utils/typedef.h"

namespace coconut {

namespace classfile {

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

  /*! \brief Entry of a file. */
  class FileEntry {
   public:
    /*! \brief Path of the file. */
    std::string path;

    /*! \brief Type of this entry. */
    enum { COMPRESS, WILDCARD, DIRECTORY } type;

    /*!
     * \brief Default constructor.
     * \param _path The file path.
     */
    FileEntry(const std::string& _path);

    friend bool operator==(const FileEntry& entry1, const FileEntry& entry2) {
      return entry1.path == entry2.path && entry1.type == entry2.type;
    }

    /*! \brief Open this file. */
    void open();

    /*! \brief Default destructor. */
    ~FileEntry() {
      if (openFlag && type == COMPRESS) {
        zip_close(zip);
      }
    }

    /*!
     * \brief Load java class file content.
     * \param className The name of the class we want to load.
     * \param buf The byte pool we want to write the content to.
     * \return The total size of this class file (bytes).
     */
    int loadClassFileBytes(const std::string& className, BYTE* buf);

   private:
    size_t MAX_BUF_SIZE = 1073741824;  // 1GB
    const std::string CLASS_SUFFIX = ".class";
    const char PACKAGE_SEPARATOR = '.';

    static bool isCompressedPackage(const std::string& path) {
      if (path.size() < 4) {
        return false;
      }
      return (path.substr(path.size() - 4, path.size()) == ".zip" ||
              path.substr(path.size() - 4, path.size()) == ".ZIP" ||
              path.substr(path.size() - 4, path.size()) == ".jar" ||
              path.substr(path.size() - 4, path.size()) == ".JAR");
    }

    static bool isWildcard(const std::string& path) {
      if (path.size() == 0) {
        return false;
      }
      return path[path.size() - 1] == '*';
    }

    bool openFlag;
    zip_t* zip;
  };

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

}  // namespace classfile

}  // namespace coconut

#endif  // SRC_CLASSFILE_FILE_LOADER_H_
