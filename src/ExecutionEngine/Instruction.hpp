/*
 *  Java Bytecode Instruction Base Class
 *  and FrameExecutor: a wrapper for StackFrame, used to help instructions be executed
 */

#pragma once

#include "../utils/ByteReader.hpp"
#include "../utils/typedef.hpp"

// for executor
#include "../RuntimeDataAreas/Thread.hpp"


namespace coconut {

class FrameExecutor;

struct Instruction {

    virtual ~Instruction() {}

    virtual void accept(ByteReader* decoder) = 0;

    virtual void accept(FrameExecutor* executor) = 0;
};

class FrameExecutor {
    private:
        Thread*  thread;

    public:
        StackFrame*     frame;

        void visit(Instruction* inst) {
            inst->accept(this);
        }

        void branch(int offset) {
            frame->nextPc = thread->pc + offset;
        }
};

struct InstWitoutOperand: public Instruction {
    void accept(ByteReader* reader) {
        // do nothing
    }
};

struct InstWithOffset: public Instruction {
    int offset;

    void accept(ByteReader* reader) {
        offset = int(reader->fetchInt16());
    }
};

}