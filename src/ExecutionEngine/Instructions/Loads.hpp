/*
 *  Loads:
 *    iload, lload, fload, dload, aload, iaload, laload, faload, daload, aaload, baload, caload, saload
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct INS_iload: public InstWithIndex {

    INS_iload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(
            executor->frame->localVariableTable->getInt(index)
        );
    }
};

struct INS_lload: public InstWithIndex {

    INS_lload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushLong(
            executor->frame->localVariableTable->getLong(index)
        );
    }
};

struct INS_fload: public InstWithIndex {

    INS_fload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushFloat(
            executor->frame->localVariableTable->getFloat(index)
        );
    }
};

struct INS_dload: public InstWithIndex {

    INS_dload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushDouble(
            executor->frame->localVariableTable->getDouble(index)
        );
    }
};

struct INS_aload: public InstWithIndex {

    INS_aload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushRef(
            executor->frame->localVariableTable->getRef(index)
        );
    }
};

struct INS_iaload: public InstWithoutOperand {

    void accept(FrameExecutor* executor) {
        int index = executor->frame->operandStack->popInt();
        Object* arrayref = executor->frame->operandStack->popRef();

        // TODO

    }
};

}