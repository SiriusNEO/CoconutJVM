/*
 *  Java Bytecode Interpreter
 */

#pragma once

#include "BytecodeDecoder.hpp"
#include "../ClassLoader/ClassInfo.hpp"


namespace coconut {

class Interpreter {
    private:
        BytecodeDecoder* decoder;

        void loop(Thread* thread) {
            FrameExecutor executor(thread, thread->stack.topFrame);

            while (true) {
                thread->pc = executor.frame->nextPc;
                decoder->reader.cursor = thread->pc;

                // new
                Instruction* newInst = decoder->getInst();
                decoder->getOperands(newInst);
                executor.frame->nextPc = decoder->reader.cursor;
                Log::info("execute inst: %d\n", thread->pc);
                executor.execute(newInst);
                delete newInst;
            }
        }

    public:
        Interpreter(): decoder(nullptr) {}
        ~Interpreter() {
            if (decoder != nullptr) {
                delete decoder;
            }
        }

        void interpret(MethodInfo& methodInfo) {
            CodeAttr* codeAttr = methodInfo.attributes->filtCodeAttr();

            if (codeAttr == nullptr) {
                panic("no code attr!");
            }

            // load code
            decoder = new BytecodeDecoder(codeAttr->codeLen, codeAttr->code);

            Thread thread;
            thread.stack.push(codeAttr->maxLocals, codeAttr->maxStack);
        }

};

}