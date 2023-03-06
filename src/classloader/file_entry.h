/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/file_entry.h
 * \brief File entries when loading class files.
 * \author SiriusNEO
 */

#include <zip/zip.h>

#include "../utils/typedef.h"

#ifndef SRC_CLASSLOADER_FILE_ENTRY_H_
#define SRC_CLASSLOADER_FILE_ENTRY_H_

namespace coconut {

namespace classloader {

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

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_FILE_ENTRY_H_
