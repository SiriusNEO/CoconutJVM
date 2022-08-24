/*
 *  The method of string splitting
 */

#pragma once

#include <string>
#include <vector>

namespace cocotools {

void split(const std::string& originStr, char delim, std::vector<std::string>& ret) {
    for (int i = 0, j = 0; i < originStr.size(); ) {
        while (j < originStr.size() && originStr[j] != delim) ++j;
        ret.push_back(originStr.substr(i, j-i));
        while (j < originStr.size() && originStr[j] == delim) ++j;
        i = j;
    }
}

}