/*
 *  Java Bytecode Instruction Base Class
 *  and FrameExecutor: a wrapper for StackFrame, used to help instructions be executed
 */

#pragma once

#include "../utils/ByteReader.hpp"
#include "../utils/typedef.hpp"
#include "../utils/Log.hpp"

// for executor
#include "../RuntimeDataAreas/Thread.hpp"


namespace coconut {

class FrameExecutor;

struct Instruction {

    virtual ~Instruction() {}

    virtual void accept(ByteReader* reader) = 0;

    virtual void accept(FrameExecutor* executor) = 0;
};

class FrameExecutor {
    private:
        Thread*  thread;

    public:
        StackFrame*     frame;

        FrameExecutor(Thread* _thread, StackFrame* _frame): thread(_thread), frame(_frame) {}

        void execute(Instruction* inst) {
            inst->accept(this);
        }

        void branch(int offset) {
            frame->nextPc = thread->pc + offset;
        }
};

struct InstWithoutOperand: public Instruction {
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

struct InstWithIndex: public Instruction {
    unsigned int index;
    bool preset;

    InstWithIndex(unsigned int _index, bool _preset) : index(_index), preset(_preset) {
        // if _preset is true, arg _index is meaningless
    }

    void accept(ByteReader* reader) {
        if (!preset) {
            index = (unsigned int)(reader->fetchU1());
        }
    }
};

struct InstWithWideIndex: public Instruction {
    unsigned int index;

    void accept(ByteReader* reader) {
        index = (unsigned int)(reader->fetchU2());
    }
};

}