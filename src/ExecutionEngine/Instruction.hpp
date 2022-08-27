/*
 *  Java Bytecode Instruction Base Class
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

class BytecodeDecoder {
    public:
        ByteReader reader;

        BytecodeDecoder(size_t codeLen, BYTE* code): reader(codeLen, code) {}

        // call new. remember to delete
        static Instruction* instructionFactory(uint8_t opcode);

        Instruction* getInst() {
            return instructionFactory(reader.fetchU1());
        }

        void getOperands(Instruction* inst) {
            inst->accept(&this->reader);
        }
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