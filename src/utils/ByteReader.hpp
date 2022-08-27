/*
 *  ByteReader: 
 *     a byte mem pool with some reading methods.
 */

#pragma once


#include "../utils/panic.hpp"
#include "../utils/typedef.hpp"


namespace coconut {

using namespace cocotools;

class ByteReader {
    public:
        BYTE* bytePool;

    private:
        int startIdx;
        size_t poolSize;

        // rust-like
        bool   borrowFlag;

        void checkOverflow(int preReadNum) {
            if (startIdx + preReadNum > poolSize) {
                panic("ByteReader bytePool overflow!");
            }
        }

    public:
        ByteReader(size_t _poolSize): startIdx(0), poolSize(_poolSize) {
            bytePool = new BYTE[poolSize];
            borrowFlag = false;
        }

        ByteReader(size_t _poolSize, BYTE* _bytePool): startIdx(0), poolSize(_poolSize), bytePool(_bytePool) {
            borrowFlag = true;
        }

        ~ByteReader() {
            if (!borrowFlag) {
                delete[] bytePool;
            }
        }

        bool good() {
            return startIdx < poolSize;
        }

        uint8_t fetchU1() {
            checkOverflow(1);
            return uint8_t(bytePool[startIdx++]);
        }

        uint16_t fetchU2() {
            checkOverflow(2);
            return (uint16_t(fetchU1()) << 8) | uint16_t(fetchU1());
        }

        uint32_t fetchU4() {
            checkOverflow(4);
            return (uint32_t(fetchU2()) << 16) | uint32_t(fetchU2());
        }

        int8_t fetchInt8() {
            return int8_t(fetchU1());
        }

        int16_t fetchInt16() {
            return int16_t(fetchU2());
        }

        int32_t fetchInt32() {
            return int32_t(fetchU4());
        }

        uint64_t fetchU8() {
            checkOverflow(8);
            return (uint64_t(fetchU4()) << 32) | uint64_t(fetchU4());
        }

        void fetchBytes(size_t byteNum, std::vector<BYTE>& buffer) {
            checkOverflow(byteNum);
            for (size_t i = 0; i < byteNum; ++i) {
                buffer.push_back((BYTE)fetchU1());
            }
        }

        void fetchBytes(size_t byteNum, BYTE* buffer) {
            checkOverflow(byteNum);
            for (size_t i = 0; i < byteNum; ++i) {
                buffer[i] = ((BYTE)fetchU1());
            }
        }

        void fetchU2List(std::vector<uint16_t>& buffer) {
            checkOverflow(1);
            uint16_t n = this->fetchU2();
            checkOverflow(2*n);
            for (uint16_t i = 0; i < n; ++i) {
                buffer.push_back(fetchU2());
            }
        }
};

}