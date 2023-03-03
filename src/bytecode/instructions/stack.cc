/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/stack.h
 * \brief Stack: pop, dup, swap
 * \author SiriusNEO
 */

#include "stack.h"

namespace coconut {

namespace bytecode {

void Inst_pop::accept(FrameExecutor* executor) {
  executor->frame->operandStack->popSlot();
  if (is_two_) executor->frame->operandStack->popSlot();  // repeat. pop two.
}

void Inst_dup::accept(FrameExecutor* executor) {
  rtda::Slot value = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value);
  executor->frame->operandStack->pushSlot(value);
}

void Inst_dup_x1::accept(FrameExecutor* executor) {
  rtda::Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value1);
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
}

void Inst_dup_x2::accept(FrameExecutor* executor) {
  rtda::Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot(),
             value3 = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value1);
  executor->frame->operandStack->pushSlot(value3);
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
}

void Inst_dup2::accept(FrameExecutor* executor) {
  rtda::Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
}

void Inst_dup2_x1::accept(FrameExecutor* executor) {
  rtda::Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot(),
             value3 = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
  executor->frame->operandStack->pushSlot(value3);
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
}

void Inst_dup2_x2::accept(FrameExecutor* executor) {
  rtda::Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot(),
             value3 = executor->frame->operandStack->popSlot(),
             value4 = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
  executor->frame->operandStack->pushSlot(value4);
  executor->frame->operandStack->pushSlot(value3);
  executor->frame->operandStack->pushSlot(value2);
  executor->frame->operandStack->pushSlot(value1);
}

void Inst_swap::accept(FrameExecutor* executor) {
  rtda::Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot();
  executor->frame->operandStack->pushSlot(value1);
  executor->frame->operandStack->pushSlot(value2);
}

}  // namespace bytecode

}  // namespace coconut
