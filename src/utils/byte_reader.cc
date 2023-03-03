/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/byte_reader.cc
 * \brief Implementation of byte_reader.h
 * \author SiriusNEO
 */

#include "byte_reader.h"

namespace coconut {

namespace utils {

uint8_t ByteReader::fetchU1() {
  checkOverflow_(1);
  return uint8_t(bytePool[cursor++]);
}

uint16_t ByteReader::fetchU2() {
  checkOverflow_(2);
  return (uint16_t(fetchU1()) << 8) | uint16_t(fetchU1());
}

uint32_t ByteReader::fetchU4() {
  checkOverflow_(4);
  return (uint32_t(fetchU2()) << 16) | uint32_t(fetchU2());
}

int8_t ByteReader::fetchInt8() { return int8_t(fetchU1()); }

int16_t ByteReader::fetchInt16() { return int16_t(fetchU2()); }

int32_t ByteReader::fetchInt32() { return int32_t(fetchU4()); }

uint64_t ByteReader::fetchU8() {
  checkOverflow_(8);
  return (uint64_t(fetchU4()) << 32) | uint64_t(fetchU4());
}

void ByteReader::fetchBytes(size_t byteNum, std::vector<BYTE>& buffer) {
  checkOverflow_(byteNum);
  for (size_t i = 0; i < byteNum; ++i) {
    buffer.push_back((BYTE)fetchU1());
  }
}

void ByteReader::fetchBytes(size_t byteNum, BYTE* buffer) {
  checkOverflow_(byteNum);
  for (size_t i = 0; i < byteNum; ++i) {
    buffer[i] = ((BYTE)fetchU1());
  }
}

void ByteReader::padding4Bytes() {
  while (cursor % 4 != 0) cursor++;
}

void ByteReader::fetchU2List(std::vector<uint16_t>& buffer) {
  checkOverflow_(1);
  uint16_t n = this->fetchU2();
  checkOverflow_(2 * n);
  for (uint16_t i = 0; i < n; ++i) {
    buffer.push_back(fetchU2());
  }
}

void ByteReader::fetchInt32List(int intNum, std::vector<int>& buffer) {
  checkOverflow_(4 * intNum);
  for (uint16_t i = 0; i < intNum; ++i) {
    buffer.push_back(fetchInt32());
  }
}

}  // namespace utils

}  // namespace coconut
