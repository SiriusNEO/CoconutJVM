/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/extended.cc
 * \brief Implementation of extended.h
 * \author SiriusNEO
 */

#include "extended.h"

namespace coconut {

namespace bytecode {

void Inst_wide::accept(utils::ByteReader* reader) { modified_->accept(reader); }

void Inst_wide::accept(FrameExecutor* executor) { modified_->accept(executor); }

void Inst_ifnull::accept(FrameExecutor* executor) {
  rtda::Object* value = executor->frame->operandStack->popRef();
  if (value == nullptr) {
    executor->branch(offset_);
  }
}

void Inst_ifnonnull::accept(FrameExecutor* executor) {
  rtda::Object* value = executor->frame->operandStack->popRef();
  if (value != nullptr) {
    executor->branch(offset_);
  }
}

void Inst_goto_w::accept(utils::ByteReader* reader) {
  offset_ = reader->fetchInt32();
}

void Inst_goto_w::accept(FrameExecutor* executor) { executor->branch(offset_); }

}  // namespace bytecode

}  // namespace coconut
