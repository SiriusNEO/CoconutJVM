/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/jvm_stack.cc
 * \brief Implementation of jvm_stack.h
 * \author SiriusNEO
 */

#include "jvm_stack.h"

namespace coconut {

namespace rtda {

void JVMStack::push(unsigned int maxLocals, unsigned int maxStack) {
  // TODO: Made it a Java exception (StackOverflowError).
  CHECK(size < capacity_) << "java.lang.StackOverflowError";
  if (isEmpty()) {
    topFrame = new StackFrame(maxLocals, maxStack, nullptr);
  } else {
    topFrame = new StackFrame(maxLocals, maxStack, topFrame);
  }
  ++size;
}

void JVMStack::pop() {
  CHECK(!isEmpty()) << "JVMStack is empty! can not pop.";
  StackFrame* popped = topFrame;
  topFrame = topFrame->lowerFrame;
  delete popped;
}

}  // namespace rtda

}  // namespace coconut
