/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/slot.cc
 * \brief Implementation of slot.h
 * \author SiriusNEO
 */

#include "slot.h"

namespace coconut {

namespace rtda {

std::string SlotList::brief() {
  std::ostringstream s;
  s << "locals: " << getInt(0) << " " << getInt(1) << " " << getInt(2);
  return s.str();
}

void SlotList::setInt(unsigned int index, int32_t val) {
  checkOverflow_(index);
  slots_[index].bytes = val;
}

int32_t SlotList::getInt(unsigned int index) {
  checkOverflow_(index);
  return int32_t(slots_[index].bytes);
}

void SlotList::setFloat(unsigned int index, float val) {
  checkOverflow_(index);
  // turn float into Slot32 (bitwise)
  // if you use (Slot)(val), round up will happen
  slots_[index].bytes = *(Slot32*)(&val);
}

float SlotList::getFloat(unsigned int index) {
  checkOverflow_(index);
  return *(float*)(&slots_[index].bytes);
}

void SlotList::setLong(unsigned int index, long long val) {
  checkOverflow_(index + 1);
  // low
  slots_[index].bytes = Slot32(val);
  // high
  slots_[index + 1].bytes = Slot32(val >> 32);
}

long long SlotList::getLong(unsigned int index) {
  checkOverflow_(index + 1);
  return (((long long)(slots_[index + 1].bytes) << 32) |
          (long long)(slots_[index].bytes));
}

void SlotList::setDouble(unsigned int index, double val) {
  setLong(index, *(long long*)(&val));
}

double SlotList::getDouble(unsigned int index) {
  long long bits = getLong(index);
  return *(double*)(&bits);
}

void SlotList::setRef(unsigned int index, Object* ref) {
  checkOverflow_(index);
  slots_[index].ref = ref;
}

Object* SlotList::getRef(unsigned int index) {
  checkOverflow_(index);
  return slots_[index].ref;
}

}  // namespace rtda

}  // namespace coconut
