/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/control.cc
 * \brief Implementation of control.h
 * \author SiriusNEO
 */

#include "control.h"

namespace coconut {

namespace bytecode {

void Inst_goto::accept(FrameExecutor* executor) { executor->branch(offset_); }

void Inst_tableswitch::accept(utils::ByteReader* reader) {
  reader->padding4Bytes();
  defaultOffset_ = reader->fetchInt32();
  low_ = reader->fetchInt32();
  high_ = reader->fetchInt32();
  reader->fetchInt32List(high_ - low_ + 1, jumpOffsets_);
}

void Inst_tableswitch::accept(FrameExecutor* executor) {
  int index = executor->frame->operandStack->popInt();
  if (index >= low_ && index <= high_)
    executor->branch(jumpOffsets_[index - low_]);
  else
    executor->branch(defaultOffset_);
}

void Inst_lookupswitch::accept(utils::ByteReader* reader) {
  reader->padding4Bytes();
  defaultOffset_ = reader->fetchInt32();
  npairs_ = reader->fetchInt32();
  reader->fetchInt32List(npairs_ << 1, matchOffsetPairs_);
}

void Inst_lookupswitch::accept(FrameExecutor* executor) {
  int key = executor->frame->operandStack->popInt();
  for (int i = 0; i < npairs_; i++) {
    if (key == matchOffsetPairs_[i << 1]) {
      executor->branch(matchOffsetPairs_[(i << 1) | 1]);
      return;
    }
  }
  executor->branch(defaultOffset_);
}

}  // namespace bytecode

}  // namespace coconut
