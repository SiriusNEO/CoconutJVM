/*
 *  Extented:
 *    wide, multianewarray, ifnull, ifnonnull, goto_w, jsr_w
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {


struct Inst_wide: public Instruction {

    Instruction* modified;

    Inst_wide(Instruction* _modified) : modified(_modified) {}

    ~Inst_wide() {
        delete modified;
    }

    void accept(ByteReader* reader) {
        modified->accept(reader);
    }

    void accept(FrameExecutor* executor) {
        modified->accept(executor);
    }
};

struct Inst_ifnull: public InstWithOffset {
    void accept(FrameExecutor* executor) {
        Object* value = executor->frame->operandStack->popRef();
        if (value == nullptr) {
            executor->branch(offset);
        }
    }
};

struct Inst_ifnonnull: public InstWithOffset {
    void accept(FrameExecutor* executor) {
        Object* value = executor->frame->operandStack->popRef();
        if (value != nullptr) {
            executor->branch(offset);
        }
    }
};

struct Inst_goto_w: public Instruction {
    int offset;

    void accept(ByteReader* reader) {
        offset = reader->fetchInt32();
    }

    void accept(FrameExecutor* executor) {
        executor->branch(offset);
    }
};

}