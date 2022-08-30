/*
 *  Stack:
 *    pop, dup, swap
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct Inst_pop: public InstWithoutOperand {
    bool is_two;

    Inst_pop(bool _is_two) : is_two(_is_two) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->popSlot();
        if (is_two) executor->frame->operandStack->popSlot(); // repeat. pop two.
    }
};

struct Inst_dup: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value);
        executor->frame->operandStack->pushSlot(value);
    }
};

struct Inst_dup_x1: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value1);
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
    }
};

struct Inst_dup_x2: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot(),
             value3 = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value1);
        executor->frame->operandStack->pushSlot(value3);
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
    }
};

struct Inst_dup2: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
    }
};

struct Inst_dup2_x1: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot(),
             value3 = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
        executor->frame->operandStack->pushSlot(value3);
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
    }
};

struct Inst_dup2_x2: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot(),
             value3 = executor->frame->operandStack->popSlot(),
             value4 = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
        executor->frame->operandStack->pushSlot(value4);
        executor->frame->operandStack->pushSlot(value3);
        executor->frame->operandStack->pushSlot(value2);
        executor->frame->operandStack->pushSlot(value1);
    }
};

struct Inst_swap: public InstWithoutOperand {
    void accept(FrameExecutor* executor) {
        Slot value1 = executor->frame->operandStack->popSlot(),
             value2 = executor->frame->operandStack->popSlot();
        executor->frame->operandStack->pushSlot(value1);
        executor->frame->operandStack->pushSlot(value2);
    }
};

}