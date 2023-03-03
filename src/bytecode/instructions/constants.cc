/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/constants.cc
 * \brief Implementation of constants.h
 * \author SiriusNEO
 */

#include "constants.h"

namespace coconut {

namespace bytecode {

void Inst_nop::accept(FrameExecutor* executor) {
  // do nothing
}

void Inst_aconst_null::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushRef(nullptr);
}

void Inst_iconst::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(val_);
}

void Inst_lconst::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushLong(val_);
}

void Inst_fconst::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushFloat(val_);
}

void Inst_dconst::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushDouble(val_);
}

void Inst_bipush::accept(utils::ByteReader* reader) {
  imm_ = int(reader->fetchInt8());  // sign-ext
}

void Inst_bipush::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(imm_);
}

void Inst_sipush::accept(utils::ByteReader* reader) {
  imm_ = int(reader->fetchInt16());  // sign-ext
}

void Inst_sipush::accept(FrameExecutor* executor) {
  executor->frame->operandStack->pushInt(imm_);
}

}  // namespace bytecode

}  // namespace coconut
