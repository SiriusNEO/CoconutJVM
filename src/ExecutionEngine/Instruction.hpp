/*
 *  Java Bytecode Instruction Base Class
 */

#pragma once

#include "../ClassLoader/ClassInfo.hpp"
#include "../RuntimeDataAreas/Thread.hpp"

namespace coconut {

class BytecodeDecoder;
class FrameExecutor;

struct Instruction {
    virtual ~Instruction() {}

    virtual void accept(BytecodeDecoder* decoder) = 0;

    virtual void accept(FrameExecutor* executor) = 0;
};


class BytecodeDecoder {
    private:
        std::vector<BYTE>*   byteStream;

    public:
        int pc;

        BytecodeDecoder(std::vector<BYTE>*  _byteStream): pc(0), byteStream(_byteStream) {}

        uint8_t fetchU1() {
            return (*byteStream)[pc++];
        }

        uint16_t fetchU2() {
            uint16_t high = fetchU1(), low = fetchU1();
            return ((high << 8) | low);
        }

        uint32_t fetchU4() {
            uint32_t high = fetchU2(), low = fetchU2();
            return ((high << 16) | low);
        }

        void getOperands(Instruction* inst) {
            inst->accept(this);
        }
};


class FrameExecutor {
    public:
        StackFrame*     frame;

        void visit(Instruction* inst) {inst->accept(this);}
};


struct InstWitoutOperand : public Instruction {
    void accept(BytecodeDecoder* decoder) {
        // do nothing
    }
};

struct InstWithOffset : public Instruction {
    int offset;
    
    // uint16_t -> int16_t -> int
    void accept(BytecodeDecoder* decoder) {
        offset = int(int16_t(decoder->fetchU2()));
    }
};


class InstWithU1Index : public Instruction {
    uint8_t index;

    void accept(BytecodeDecoder* decoder) {
        index = decoder->fetchU1();
    }
};


class InstWithU2Index : public Instruction {
    uint16_t index;

    void accept(BytecodeDecoder* decoder) {
        index = decoder->fetchU2();
    }
};


}