/*
 *  Control:
 *    goto, jsr, ret, tableswitch, lookupswitch, ireturn, lreturn, freturn, dreturn, areturn, return
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct Inst_goto: public InstWithOffset {
    void accept(FrameExecutor* executor) {
        executor->branch(offset);
    }
};

struct Inst_tableswitch: public Instruction {

    int defaultOffset, low, high;
    std::vector<int> jumpOffsets;

    void accept(ByteReader* reader) {
        reader->padding4Bytes();
        defaultOffset = reader->fetchInt32();
        low = reader->fetchInt32();
        high = reader->fetchInt32();
        reader->fetchInt32List(high-low+1, jumpOffsets);
    }

    void accept(FrameExecutor* executor) {
        int index = executor->frame->operandStack->popInt();
        if (index >= low && index <= high) executor->branch(jumpOffsets[index-low]);
        else executor->branch(defaultOffset);
    }
};

struct Inst_lookupswitch: public Instruction {

    int defaultOffset, npairs;
    std::vector<int> matchOffsetPairs;

    void accept(ByteReader* reader) {
        reader->padding4Bytes();
        defaultOffset = reader->fetchInt32();
        npairs = reader->fetchInt32();
        reader->fetchInt32List(npairs<<1, matchOffsetPairs);
    }

    void accept(FrameExecutor* executor) {
        int key = executor->frame->operandStack->popInt();
        for (int i = 0; i < npairs; i++) {
            if (key == matchOffsetPairs[i<<1]) {
                executor->branch(matchOffsetPairs[(i<<1)|1]);
                return;
            }
        }
        executor->branch(defaultOffset);
    }
};

}