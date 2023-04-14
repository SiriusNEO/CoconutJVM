/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/file_entry.cc
 * \brief Implementation of file_entry.h
 * \author SiriusNEO
 */

#include "file_entry.h"

#include <sys/stat.h>
#include <unistd.h>

#include "../utils/logging.h"

namespace coconut {

namespace classloader {

FileEntry::FileEntry(const std::string& _path) : path(_path), openFlag(false) {
  if (isWildcard(path)) {
    type = WILDCARD;
    path = path.substr(0, path.size() - 1);
  } else if (isCompressedPackage(path))
    type = COMPRESS;
  else {
    type = DIRECTORY;
    if (path[path.size() - 1] != '/') {
      path += "/";
    }
  }

  CHECK(access(path.c_str(), F_OK) == 0)
      << "File loader error: Path: %s not exists: " << path.c_str();

  // WILDCARD and DIRECTORY all need checking
  if (type != COMPRESS) {
    struct stat statbuf;
    CHECK(stat(path.c_str(), &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
        << "File loader error: Path: %s not a directory: " << path.c_str();
  }
}

void FileEntry::open() {
  if (type == WILDCARD) {
    LOG(FATAL) << "File loader error: Wildcard not be eliminated!";
  } else if (type == COMPRESS) {
    zip = zip_open(path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
  }
  openFlag = true;
}

int FileEntry::loadClassFileBytes(const std::string& className, BYTE* buf) {
  CHECK(openFlag) << "File loader error: Read in closed entry: " << path;

  std::string classLocation = className;

  if (type == COMPRESS) {
    for (char& ch : classLocation) {
      if (ch == PACKAGE_SEPARATOR) {
        ch = '/';
      }
    }
    classLocation += CLASS_SUFFIX;
    LOG(INFO) << "read: " << classLocation.c_str();
    int code = zip_entry_open(zip, classLocation.c_str());
    if (code < 0) {
      return -1;
    } else {
      size_t buf_size = zip_entry_size(zip);
      CHECK(zip_entry_noallocread(zip, (void*)buf, buf_size) >= 0)
          << "File loader error: when loading class " << classLocation.c_str();
      zip_entry_close(zip);
      return buf_size;
    }
  } else {
    CHECK(type == DIRECTORY);
    classLocation += CLASS_SUFFIX;
    LOG(INFO) << "read: " << (path + classLocation).c_str();
    std::ifstream fs(path + classLocation,
                     std::ios_base::binary | std::ios_base::in);
    if (fs.fail()) {
      return false;
    }
    fs.read((char*)buf, MAX_BUF_SIZE);
    return fs.gcount();
  }
}

}  // namespace classloader

}  // namespace coconut
