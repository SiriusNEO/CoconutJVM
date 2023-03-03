/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/local_variable_table.cc
 * \brief Implementation of local_variable_table.h
 * \author SiriusNEO
 */

#include "local_variable_table.h"

namespace coconut {

namespace rtda {

std::string LocalVariableTable::brief() {
  std::ostringstream s;
  s << "locals: " << getInt(0) << " " << getInt(1) << " " << getInt(2);
  return s.str();
}

void LocalVariableTable::setInt(unsigned int index, int32_t val) {
  checkOverflow_(index);
  slots_[index].bytes = val;
}

int32_t LocalVariableTable::getInt(unsigned int index) {
  checkOverflow_(index);
  return int32_t(slots_[index].bytes);
}

void LocalVariableTable::setFloat(unsigned int index, float val) {
  checkOverflow_(index);
  // turn float into Slot32 (bitwise)
  // if you use (Slot)(val), round up will happen
  slots_[index].bytes = *(Slot32*)(&val);
}

float LocalVariableTable::getFloat(unsigned int index) {
  checkOverflow_(index);
  return *(float*)(&slots_[index].bytes);
}

void LocalVariableTable::setLong(unsigned int index, long long val) {
  checkOverflow_(index + 1);
  // low
  slots_[index].bytes = Slot32(val);
  // high
  slots_[index + 1].bytes = Slot32(val >> 32);
}

long long LocalVariableTable::getLong(unsigned int index) {
  checkOverflow_(index + 1);
  return (((long long)(slots_[index + 1].bytes) << 32) |
          (long long)(slots_[index].bytes));
}

void LocalVariableTable::setDouble(unsigned int index, double val) {
  setLong(index, *(long long*)(&val));
}

double LocalVariableTable::getDouble(unsigned int index) {
  long long bits = getLong(index);
  return *(double*)(&bits);
}

void LocalVariableTable::setRef(unsigned int index, Object* ref) {
  checkOverflow_(index);
  slots_[index].ref = ref;
}

Object* LocalVariableTable::getRef(unsigned int index) {
  checkOverflow_(index);
  return slots_[index].ref;
}

}  // namespace rtda

}  // namespace coconut
