/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classfile/file_loader.cc
 * \brief Implementation of file_loader.h
 * \author SiriusNEO
 */

#include "file_loader.h"

namespace coconut {

namespace classfile {

FileLoader::FileEntry::FileEntry(const std::string& _path)
    : path(_path), openFlag(false) {
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

void FileLoader::FileEntry::open() {
  if (type == WILDCARD) {
    LOG(FATAL) << "File loader error: Wildcard not be eliminated!";
  } else if (type == COMPRESS) {
    zip = zip_open(path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
  }
  openFlag = true;
}

int FileLoader::FileEntry::loadClassFileBytes(const std::string& className,
                                              BYTE* buf) {
  CHECK(openFlag) << "File loader error: Read in closed entry.";

  std::string classLocation = className;

  if (type == COMPRESS) {
    for (char& ch : classLocation) {
      if (ch == PACKAGE_SEPARATOR) {
        ch = '/';
      }
    }
    classLocation += CLASS_SUFFIX;
    LOG(INFO) << "read: %s", classLocation.c_str();
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

FileLoader::FileLoader(const std::string& prefix, const std::string& path) {
  std::vector<std::string> singlePaths;
  utils::split(path, PATH_SEPARATOR, singlePaths);

  CHECK(singlePaths.size() <= MAX_PATH_NUM)
      << "File loader error: Too much paths";

  std::vector<FileEntry> tmpEntries;
  // construct entries
  for (const std::string& singlePath : singlePaths) {
    tmpEntries.push_back(FileEntry(prefix + singlePath));
  }

  // unpack wildcard entries
  std::vector<FileEntry> tmpEntries1;
  while (!tmpEntries.empty()) {
    FileEntry lastEntry = tmpEntries.back();
    tmpEntries.pop_back();

    if (lastEntry.type == FileEntry::WILDCARD) {
      // WILDCARD: unpack all .jar files
      DIR* wildcardDir = opendir(lastEntry.path.c_str());
      CHECK(wildcardDir != nullptr);
      dirent* dirPointer = readdir(wildcardDir);
      for (; dirPointer != nullptr; dirPointer = readdir(wildcardDir)) {
        std::string nowFn = dirPointer->d_name;
        if (nowFn.size() > 4 &&
            (nowFn.substr(nowFn.size() - 4, nowFn.size()) == ".jar" ||
             nowFn.substr(nowFn.size() - 4, nowFn.size()) == ".JAR")) {
          tmpEntries1.push_back(FileEntry(prefix + lastEntry.path + nowFn));
        }
      }
      closedir(wildcardDir);
    } else {
      tmpEntries1.push_back(lastEntry);
    }
  }

  // remove the redundant entries
  while (!tmpEntries1.empty()) {
    FileEntry lastEntry = tmpEntries1.back();
    tmpEntries1.pop_back();

    bool hasEqual = false;
    for (const auto& entry : entries) {
      if (entry == lastEntry) {
        hasEqual = true;
        break;
      }
    }

    if (!hasEqual) {
      entries.push_back(lastEntry);
    }
  }

  for (auto& entry : entries) {
    entry.open();
    LOG(INFO) << "Entry. Path=" << entry.path.c_str() << " Type=" << entry.type;
  }
}

int FileLoader::loadClassFileBytes(const std::string& className, BYTE* buf) {
  for (auto& entry : entries) {
    int ret = entry.loadClassFileBytes(className, buf);
    if (ret > 0) return ret;
  }
  return -1;
}

}  // namespace classfile

}  // namespace coconut
