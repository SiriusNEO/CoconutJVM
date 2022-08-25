/*
 *  Modified UTF8
 */

#pragma once

#include "typedef.hpp"
#include "Log.hpp"
#include "panic.hpp"
#include <vector>
#include <string>
#include "../../3rdparty/utf16/converter.h"

namespace cocotools {

// reference: https://github.com/sciencesakura/mutf-8/blob/master/src/index.ts

#define UTF_BUFFER 12

std::string Utf16fromBytes(utf16_t* bytes, size_t size) {
    utf8_t  utf8_bc[size << 2];
    size_t utf8_size = utf16_to_utf8(bytes, size, utf8_bc, size << 2);
    auto ret = std::string(utf8_bc, utf8_bc + utf8_size);
    return ret;
}

void DECODE_ERROR() {
    panic("mutf8 decode error");
}

std::string decodeMUTF8FromBytes(const std::vector<BYTE>& bytesStream) {
    // Notice: this only support utf-8
    // return std::string(bytesStream.begin(), bytesStream.end());

    // this code seems to work.
    // return std::string(utf8) can be directly printed in console

    int ptr = 0;
    utf16_t* utf16_buffer = new utf16_t[bytesStream.size()];
    size_t utf16_size = 0;

    while (ptr < bytesStream.size()) {
        utf16_t b1 = bytesStream[ptr++];

        if (!(b1 & 0x80) && b1 != 0) {
            utf16_buffer[utf16_size++] = b1;
        }
        else if ((b1 >> 5) == 0b110) {
            // Log::info("two");
            if (ptr >= bytesStream.size()) {
                DECODE_ERROR();
            }
            utf16_t b2 = bytesStream[ptr++];
            if ((b2 >> 6) != 0b10) {
                DECODE_ERROR();
            }
            utf16_buffer[utf16_size++] = (((b1 & 0x1f) << 6) | (b2 & 0x3f));
        }
        else if ((b1 >> 4) == 0b1110) {
            // Log::info("three");
            if (ptr+1 >= bytesStream.size()) {
                DECODE_ERROR();
            }
            utf16_t b2 = bytesStream[ptr++], b3 = bytesStream[ptr++];
            if ((b2 >> 6) != 0b10 || (b3 >> 6) != 0b10) {
                DECODE_ERROR();
            }
            utf16_buffer[utf16_size++] = (((b1 & 0x0f) << 12) | ((b2 & 0x3f) << 6) | (b3 & 0x3f));
        }
        else {
            DECODE_ERROR();
        }
    }

    std::string ret = Utf16fromBytes(utf16_buffer, utf16_size);
    delete[] utf16_buffer;
    
    return ret;
}

}