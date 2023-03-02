/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/stores.cc
 * \brief Implementation of stores.h
 * \author SiriusNEO
 */

#include "stores.h"

namespace coconut {

namespace bytecode {

void Inst_istore::accept(FrameExecutor* executor) {
  executor->frame->localVariableTable->setInt(
      index_, executor->frame->operandStack->popInt());
}

void Inst_lstore::accept(FrameExecutor* executor) {
  executor->frame->localVariableTable->setLong(
      index_, executor->frame->operandStack->popLong());
}

void Inst_fstore::accept(FrameExecutor* executor) {
  executor->frame->localVariableTable->setFloat(
      index_, executor->frame->operandStack->popFloat());
}

void Inst_dstore::accept(FrameExecutor* executor) {
  executor->frame->localVariableTable->setDouble(
      index_, executor->frame->operandStack->popDouble());
}

void Inst_astore::accept(FrameExecutor* executor) {
  executor->frame->localVariableTable->setRef(
      index_, executor->frame->operandStack->popRef());
}

void Inst_iastore::accept(FrameExecutor* executor) {
  int value = executor->frame->operandStack->popInt();
  int index = executor->frame->operandStack->popInt();
  rtda::Object* arrayref = executor->frame->operandStack->popRef();

  // TODO
}

}  // namespace bytecode

}  // namespace coconut
