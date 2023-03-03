/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/operand_stack.cc
 * \brief Implementation of operand_stack.h
 * \author SiriusNEO
 */

#include "operand_stack.h"

namespace coconut {

namespace rtda {

std::string OperandStack::brief() {
  std::ostringstream s;
  s << "stack(top=" << top_ << "): " << getSlot(0).bytes << " "
    << getSlot(1).bytes;
  return s.str();
}

Slot OperandStack::getSlot(int index) { return slots_[index]; }

void OperandStack::pushSlot(Slot slot) {
  slots_[top_] = slot;
  up();
}

Slot OperandStack::popSlot() {
  down();
  return slots_[top_];
}

void OperandStack::pushInt(int val) {
  slots_[top_].bytes = val;
  up();
}

int OperandStack::popInt() {
  down();
  return int(slots_[top_].bytes);
}

void OperandStack::pushFloat(float val) {
  slots_[top_].bytes = *(Slot32*)(&val);
  up();
}

float OperandStack::popFloat() {
  down();
  return *(float*)(&slots_[top_].bytes);
}

void OperandStack::pushLong(long long val) {
  // "low" part of long long
  slots_[top_].bytes = Slot32(val);
  up();
  // "high" part of long long
  slots_[top_].bytes = Slot32(val >> 32);
  up();
}

long long OperandStack::popLong() {
  down();
  long long high = (long long)(slots_[top_].bytes);
  down();
  long long low = (long long)(slots_[top_].bytes);
  return (long long)((high << 32) | low);
}

void OperandStack::pushDouble(double val) { pushLong(*(long long*)(&val)); }

double OperandStack::popDouble() {
  long long bits = popLong();
  return *(double*)(&bits);
}

void OperandStack::pushRef(Object* ref) {
  slots_[top_].ref = ref;
  up();
}

Object* OperandStack::popRef() {
  down();
  return slots_[top_].ref;
}

}  // namespace rtda

}  // namespace coconut
