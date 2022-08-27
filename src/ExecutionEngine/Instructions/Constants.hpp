/*
 *  Constants:
 *    nop, aconst_null, iconst, lconst, fconst, dconst, bipush, sipush, ldc
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct Inst_nop: public InstWitoutOperand {
    void accept(FrameExecutor* executor) {
        // do nothing
    }
};

struct Inst_aconst_null: public InstWitoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushRef(nullptr);
    }
};

struct Inst_iconst: public InstWitoutOperand {
    int val;

    Inst_iconst(int _val): val(_val) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(val);
    }
};

struct Inst_lconst: public InstWitoutOperand {
    long long val;

    Inst_lconst(long long _val): val(_val) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushLong(val);
    }
};

struct Inst_fconst: public InstWitoutOperand {
    float val;

    Inst_fconst(float _val): val(_val) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushFloat(val);
    }
};

struct Inst_dconst: public InstWitoutOperand {
    double val;

    Inst_dconst(double _val): val(_val) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushDouble(val);
    }
};

struct Inst_bipush: public Instruction {
    int imm;

    void accept(ByteReader* reader) {
        imm = int(reader->fetchInt8()); //sign-ext
    }

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(imm);
    }
};

struct Inst_sipush: public Instruction {
    int imm;

    void accept(ByteReader* reader) {
        imm = int(int8_t(reader->fetchU2())); //sign-ext
    }

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(imm);
    }
};

}