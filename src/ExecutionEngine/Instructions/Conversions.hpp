/*
 *  Conversions:
 *    i2b, i2c, i2s, i2f, i2l, i2d,
 *    l2i, l2f, l2d,
 *    f2i, f2l, f2d,
 *    d2i, d2l, d2f
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct Inst_i2b: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(int8_t(executor->frame->operandStack->popInt()));
    }
};

struct Inst_i2c: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(uint16_t(executor->frame->operandStack->popInt()));
    }
};

struct Inst_i2s: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(int16_t(executor->frame->operandStack->popInt()));
    }
};

struct Inst_i2l: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushLong(executor->frame->operandStack->popInt());
    }
};

struct Inst_i2f: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushFloat(executor->frame->operandStack->popInt());
    }
};

struct Inst_i2d: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushDouble(executor->frame->operandStack->popInt());
    }
};

struct Inst_l2i: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(executor->frame->operandStack->popLong());
    }
};

struct Inst_l2f: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushFloat(executor->frame->operandStack->popLong());
    }
};

struct Inst_l2d: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushDouble(executor->frame->operandStack->popLong());
    }
};

struct Inst_f2i: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(executor->frame->operandStack->popFloat());
    }
};

struct Inst_f2l: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushLong(executor->frame->operandStack->popFloat());
    }
};

struct Inst_f2d: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushDouble(executor->frame->operandStack->popFloat());
    }
};

struct Inst_d2i: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(executor->frame->operandStack->popDouble());
    }
};

struct Inst_d2l: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushLong(executor->frame->operandStack->popDouble());
    }
};

struct Inst_d2f: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushFloat(executor->frame->operandStack->popDouble());
    }
};

}