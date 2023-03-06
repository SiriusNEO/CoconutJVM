/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/file_loader.cc
 * \brief Implementation of file_loader.h
 * \author SiriusNEO
 */

#include "file_loader.h"

#include <dirent.h>

#include "../utils/logging.h"
#include "../utils/misc.h"

namespace coconut {

namespace classloader {

FileLoader::FileLoader(const std::string& prefix, const std::string& path) {
  Strings singlePaths;
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

}  // namespace classloader

}  // namespace coconut
