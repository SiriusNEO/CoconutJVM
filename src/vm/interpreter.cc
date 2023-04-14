/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/vm/interpreter.cc
 * \brief Implementation of interpreter.h
 * \author SiriusNEO
 */

#include "interpreter.h"

namespace coconut {

namespace vm {

void Interpreter::loop(rtda::Thread* thread) {
  bytecode::FrameExecutor executor(thread, thread->stack.topFrame);

  while (true) {
    thread->pc = executor.frame->nextPc;
    decoder_->reader.cursor = thread->pc;

    // new
    bytecode::Instruction* newInst = decoder_->getInst();
    decoder_->getOperands(newInst);
    executor.frame->nextPc = decoder_->reader.cursor;
    LOG(INFO) << "Execute inst: " << thread->pc;
    executor.execute(newInst);
    delete newInst;

    // operand stack
    LOG(INFO) << executor.frame->operandStack->brief();

    // local variable table. Look the first three locations.
    LOG(INFO) << executor.frame->localVariableTable->brief();
  }
}

void Interpreter::interpret(classloader::MemberInfo& methodInfo) {
  LOG(INFO) << "Interpret method: %s", methodInfo.name().c_str();

  classloader::CodeAttr* codeAttr = methodInfo.attributes->filtCodeAttr();
  CHECK(codeAttr != nullptr) << "No CodeAttr found";

  // load code
  decoder_ = new bytecode::BytecodeDecoder(codeAttr->codeLen, codeAttr->code);

  rtda::Thread thread;
  thread.stack.push(codeAttr->maxLocals, codeAttr->maxStack);
  LOG(INFO) << "thread info: maxLocals=" << codeAttr->maxLocals
            << " maxStack=%d" << codeAttr->maxStack;

  // start loop
  loop(&thread);
}

}  // namespace vm

}  // namespace coconut
