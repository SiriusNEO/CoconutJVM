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

#include "../env/path.h"
#include "../utils/logging.h"
#include "../utils/misc.h"

namespace coconut {

namespace classloader {

FileLoader::FileLoader(const std::string& jreHome, const std::string& classpath)
    : jreHome_(env::configJreHome(jreHome)),
      classpath_(env::configClasspath(classpath)) {
  // user-specified classpath
  initEntriesByClasspath(classpath_);
}

int FileLoader::loadClassFileBytes(const std::string& className, BYTE* buf) {
  int ret;

  // load from lib/*
  for (auto& entry : libEntries_) {
    ret = entry.loadClassFileBytes(className, buf);
    if (ret > 0) return ret;
  }

  // load from lib/ext/*
  for (auto& entry : extEntries_) {
    ret = entry.loadClassFileBytes(className, buf);
    if (ret > 0) return ret;
  }

  // load from entries of classpath
  for (auto& entry : entries_) {
    ret = entry.loadClassFileBytes(className, buf);
    if (ret > 0) return ret;
  }

  // load failed
  return -1;
}

void FileLoader::initEntriesByClasspath(const std::string& classpath) {
  Strings singlePaths;
  utils::split(classpath, PATH_SEPARATOR, singlePaths);

  CHECK(singlePaths.size() <= MAX_PATH_NUM)
      << "File loader error: Too much paths";

  std::vector<FileEntry> tmpEntries;
  // construct entries
  for (const std::string& singlePath : singlePaths) {
    tmpEntries.push_back(FileEntry(singlePath));
  }

  // unpack wildcard entries
  std::vector<FileEntry> tmpEntries1;
  unpackWildcardPath(tmpEntries, tmpEntries1);

  // remove the redundant entries
  while (!tmpEntries1.empty()) {
    FileEntry lastEntry = tmpEntries1.back();
    tmpEntries1.pop_back();

    bool hasEqual = false;
    for (const auto& entry : entries_) {
      if (entry == lastEntry) {
        hasEqual = true;
        break;
      }
    }

    if (!hasEqual) {
      entries_.push_back(lastEntry);
    }
  }

  tmpEntries.push_back(FileEntry(jreHome_ + "/lib/*"));
  unpackWildcardPath(tmpEntries, libEntries_);
  for (auto& entry : libEntries_) {
    entry.open();
    LOG(INFO) << "Lib Entry. Path=" << entry.path.c_str()
              << " Type=" << entry.type;
  }

  tmpEntries.push_back(FileEntry(jreHome_ + "/lib/ext/*"));
  unpackWildcardPath(tmpEntries, extEntries_);
  for (auto& entry : extEntries_) {
    entry.open();
    LOG(INFO) << "Ext Entry. Path=" << entry.path.c_str()
              << " Type=" << entry.type;
  }

  for (auto& entry : entries_) {
    entry.open();
    LOG(INFO) << "Classpath Entry. Path=" << entry.path.c_str()
              << " Type=" << entry.type;
  }
}

void FileLoader::unpackWildcardPath(std::vector<FileEntry>& fromEntries,
                                    std::vector<FileEntry>& toEntries) {
  while (!fromEntries.empty()) {
    FileEntry lastEntry = fromEntries.back();
    fromEntries.pop_back();

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
          toEntries.push_back(FileEntry(lastEntry.path + nowFn));
        }
      }
      closedir(wildcardDir);
    } else {
      toEntries.push_back(lastEntry);
    }
  }
}

}  // namespace classloader

}  // namespace coconut
