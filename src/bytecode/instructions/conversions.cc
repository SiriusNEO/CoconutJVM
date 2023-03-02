/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/conversions.cc
 * \brief Implementation of conversions.h
 * \author SiriusNEO
 */

#include "conversions.h"

namespace coconut {

namespace bytecode {

void Inst_i2b::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      int8_t(executor->frame->operandStack->popInt()));
}

void Inst_i2c::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      uint16_t(executor->frame->operandStack->popInt()));
}

void Inst_i2s::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      int16_t(executor->frame->operandStack->popInt()));
}

void Inst_i2l::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushLong(
      executor->frame->operandStack->popInt());
}

void Inst_i2f::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushFloat(
      executor->frame->operandStack->popInt());
}

void Inst_i2d::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushDouble(
      executor->frame->operandStack->popInt());
}

void Inst_l2i::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      executor->frame->operandStack->popLong());
}

void Inst_l2f::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushFloat(
      executor->frame->operandStack->popLong());
}

void Inst_l2d::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushDouble(
      executor->frame->operandStack->popLong());
}

void Inst_f2i::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      executor->frame->operandStack->popFloat());
}

void Inst_f2l::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushLong(
      executor->frame->operandStack->popFloat());
}

void Inst_f2d::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushDouble(
      executor->frame->operandStack->popFloat());
}

void Inst_d2i::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      executor->frame->operandStack->popDouble());
}

void Inst_d2l::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushLong(
      executor->frame->operandStack->popDouble());
}

void Inst_d2f::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushFloat(
      executor->frame->operandStack->popDouble());
}

}  // namespace bytecode

}  // namespace coconut
