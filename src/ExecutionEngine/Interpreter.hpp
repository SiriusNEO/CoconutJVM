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
                Log::info("execute inst: %d", thread->pc);
                executor.execute(newInst);
                delete newInst;

                // operand stack
                Log::info("stack(top=%d): %d %d", 
                executor.frame->operandStack->top,
                executor.frame->operandStack->getSlot(0).bytes, 
                executor.frame->operandStack->getSlot(1).bytes);

                // local variable table
                Log::info("locals: %d %d %d", executor.frame->localVariableTable->getInt(0), 
                 executor.frame->localVariableTable->getInt(1),  executor.frame->localVariableTable->getInt(2));

                Log::info("");
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
            cocotools::Log::info("interpret method: %s", methodInfo.fieldName().c_str());

            CodeAttr* codeAttr = methodInfo.attributes->filtCodeAttr();

            if (codeAttr == nullptr) {
                panic("no code attr!");
            }

            // load code
            decoder = new BytecodeDecoder(codeAttr->codeLen, codeAttr->code);

            Thread thread;
            thread.stack.push(codeAttr->maxLocals, codeAttr->maxStack);
            Log::info("thread info: maxLocals=%d maxStack=%d", codeAttr->maxLocals, codeAttr->maxStack);

            // start loop
            loop(&thread);
        }

};

}