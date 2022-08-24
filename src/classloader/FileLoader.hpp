/*
 *  FileLoader: 
 *      from local file loading java class information ([]byte)
 *      Support format: directory, zip/jar 
 */

#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "../utils/split.hpp"
#include "../utils/panic.hpp"
#include "../utils/log.hpp"
#include "../utils/typedef.hpp"

#include "../../3rdparty/zip/zip.h"

namespace coconut {

using namespace cocotools;

class FileLoader {

    private:
        static const int MAX_PATH_NUM = 10;
        static const char PATH_SEPARATOR =  ':';

        class FileEntry {
            public:
                std::string path;
                enum {COMPRESS, WILDCARD, DIRECTORY} type;

                FileEntry(const std::string& _path): path(_path), openFlag(false) {
                    if (isWildcard(path)) {
                        type = WILDCARD;
                        path = path.substr(0, path.size() - 1);
                    }
                    else if (isCompressedPackage(path)) type = COMPRESS;
                    else {
                        type = DIRECTORY;
                        if (path[path.size()-1] != '/') {
                            path += "/";
                        }
                    }

                    if (access(path.c_str(), F_OK) != 0) {
                        panic("path: %s not exists", path.c_str());
                    }

                    // WILDCARD and DIRECTORY all need checking
                    if (type != COMPRESS) {
                        struct stat statbuf;
                        if (stat(path.c_str(), &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
                            panic("path: %s not a directory", path.c_str());
                        }
                    }
                }

                friend bool operator==(const FileEntry& entry1, const FileEntry& entry2) {
                    return entry1.path == entry2.path && entry1.type == entry2.type;
                }

                void open() {
                    if (type == WILDCARD) {
                        panic("wildcard not be eliminated!");
                    }
                    else if (type == COMPRESS) {
                        zip = zip_open(path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
                    }
                    openFlag = true;
                }

                ~FileEntry() {
                    if (openFlag && type == COMPRESS) {
                        zip_close(zip);
                    }
                }

                int readClassFile(const std::string& className, BYTE* buf) {
                    if (!openFlag) {
                        panic("read in closed entry.");
                    }

                    std::string classLocation = className;

                    if (type == COMPRESS) {
                        for (char& ch : classLocation) {
                            if (ch == PACKAGE_SEPARATOR) {
                                ch = '/';
                            }
                        }
                        classLocation += CLASS_SUFFIX;
                        Log::info("read: %s", classLocation.c_str());
                        int code = zip_entry_open(zip, classLocation.c_str());
                        if (code < 0) {
                            return -1;
                        }
                        else {
                            size_t buf_size = zip_entry_size(zip);
                            if (zip_entry_noallocread(zip, (void *) buf, buf_size) < 0) {
                                panic("load class: %s error", classLocation.c_str());
                            }
                            return buf_size;
                        }
                    }
                    else {
                        assert(type == DIRECTORY);
                        classLocation += CLASS_SUFFIX;
                        Log::info("read: %s", (path + classLocation).c_str());
                        std::ifstream fs(path + classLocation, std::ios_base::binary | std::ios_base::in);
                        if (fs.fail()) {
                            return false;
                        }
                        fs.read((char *)buf, MAX_BUF_SIZE);
                        return fs.gcount();
                    }
                }

            private:
                size_t MAX_BUF_SIZE = 1073741824; // 1GB
                const std::string CLASS_SUFFIX = ".class";
                const char PACKAGE_SEPARATOR = '.';

                static bool isCompressedPackage(const std::string& path) {
                    if (path.size() < 4) {
                        return false;
                    }
                    return (path.substr(path.size()-4, path.size()) == ".zip" ||
                        path.substr(path.size()-4, path.size()) == ".ZIP" ||
                        path.substr(path.size()-4, path.size()) == ".jar" ||
                        path.substr(path.size()-4, path.size()) == ".JAR");
                }

                static bool isWildcard(const std::string& path) {
                    if (path.size() == 0) {
                        return false;
                    }
                    return path[path.size()-1] == '*';
                }

                bool openFlag;
                zip_t* zip;
        };

        std::vector<FileEntry> entries;

    public:
        FileLoader(const std::string& prefix, const std::string& path) {
            std::vector<std::string> singlePaths; 
            split(path, PATH_SEPARATOR, singlePaths);

            if (singlePaths.size() > MAX_PATH_NUM) {
                panic("too much path");
            }

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
                    assert(wildcardDir != nullptr);
                    dirent* dirPointer = readdir(wildcardDir);
                    for (; dirPointer != nullptr; dirPointer = readdir(wildcardDir)) {
                        std::string nowFn = dirPointer->d_name;
                        if (nowFn.size() > 4 && (nowFn.substr(nowFn.size()-4, nowFn.size()) == ".jar" ||
                        nowFn.substr(nowFn.size()-4, nowFn.size()) == ".JAR")) {
                            tmpEntries1.push_back(FileEntry(prefix + lastEntry.path + nowFn));
                        }
                    }
                    closedir(wildcardDir);
                }
                else {
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

            for (auto& entry: entries) {
                entry.open();
                Log::info("Entry. Path=%s Type=%d", entry.path.c_str(), entry.type);
            }
        }

        int readClassFile(const std::string& className, BYTE* buf) {
            for (auto& entry: entries) {
                int ret = entry.readClassFile(className, buf);
                if (ret > 0) return ret;
            }
            return -1;
        }
};

}