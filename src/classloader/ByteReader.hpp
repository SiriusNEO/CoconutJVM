/*
 *  ByteReader: 
 *     a byte mem pool with some reading methods.
 */

#pragma once


#include "../utils/panic.hpp"
#include "../utils/typedef.hpp"
#include <vector>

namespace coconut {

using namespace cocotools;

class ByteReader {
    private:
        int startIdx;
        size_t poolSize;
        BYTE* bytePool;

        void checkOverflow(int preReadNum) {
            if (startIdx + preReadNum > poolSize) {
                panic("ByteReader bytePool overflow!");
            }
        }

    public:
        ByteReader(size_t _poolSize): startIdx(0), poolSize(_poolSize) {
            bytePool = new BYTE[poolSize];
        }

        ~ByteReader() {
            delete[] bytePool;
        }

        bool good() {
            return startIdx < poolSize;
        }

        uint8_t fetchU1() {
            checkOverflow(1);
            return uint8_t(bytePool[startIdx++]);
        }

        
        void fetchBytes(int byteNum, std::vector<BYTE>& buffer) {
            checkOverflow(byteNum);
            for (int i = 0; i < byteNum; ++i, ++startIdx) {
                buffer.push_back(bytePool[startIdx]);
            }
        }

        uint16_t fetchU2() {
            checkOverflow(2);
            uint16_t ret = *((uint16_t*)(bytePool+startIdx));
            startIdx += 2;
            return ret;
        }

        void fetchU2List(std::vector<uint16_t>& buffer) {
            checkOverflow(1);
            uint16_t n = this->fetchU2();
            checkOverflow(2*n);
            for (uint16_t i = 0; i < n; ++i, startIdx+=2) {
                buffer.push_back(*((uint16_t*)(bytePool+startIdx)));
            }
        }

        uint32_t fetchU4() {
            checkOverflow(4);
            uint32_t ret = *((uint32_t*)(bytePool+startIdx));
            startIdx += 4;
            return ret;
        }

        uint64_t fetchU8() {
            checkOverflow(8);
            uint64_t ret = *((uint64_t*)(bytePool+startIdx));
            startIdx += 8;
            return ret;
        }
};

}