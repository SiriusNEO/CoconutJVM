/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/loads.cc
 * \brief Implementation of loads.h
 * \author SiriusNEO
 */

#include "loads.h"

namespace coconut {

namespace bytecode {

void Inst_iload::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(
      executor->frame->localVariableTable->getInt(index_));
}

void Inst_lload::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushLong(
      executor->frame->localVariableTable->getLong(index_));
}

void Inst_fload::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushFloat(
      executor->frame->localVariableTable->getFloat(index_));
}

void Inst_dload::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushDouble(
      executor->frame->localVariableTable->getDouble(index_));
}

void Inst_aload::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushRef(
      executor->frame->localVariableTable->getRef(index_));
}

void Inst_iaload::accept(FrameExecutor* executor) {
  int index = executor->frame->operandStack->popInt();
  rtda::Object* arrayref = executor->frame->operandStack->popRef();

  // TODO
}

}  // namespace bytecode

}  // namespace coconut
