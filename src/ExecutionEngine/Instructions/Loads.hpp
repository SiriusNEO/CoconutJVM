/*
 *  Loads:
 *    iload, lload, fload, dload, aload, iaload, laload, faload, daload, aaload, baload, caload, saload
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct Inst_iload: public InstWithIndex {

    Inst_iload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushInt(
            executor->frame->localVariableTable->getInt(index)
        );
    }
};

struct Inst_lload: public InstWithIndex {

    Inst_lload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushLong(
            executor->frame->localVariableTable->getLong(index)
        );
    }
};

struct Inst_fload: public InstWithIndex {

    Inst_fload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushFloat(
            executor->frame->localVariableTable->getFloat(index)
        );
    }
};

struct Inst_dload: public InstWithIndex {

    Inst_dload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushDouble(
            executor->frame->localVariableTable->getDouble(index)
        );
    }
};

struct Inst_aload: public InstWithIndex {

    Inst_aload(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->operandStack->pushRef(
            executor->frame->localVariableTable->getRef(index)
        );
    }
};

struct Inst_iaload: public InstWithoutOperand {

    void accept(FrameExecutor* executor) {
        int index = executor->frame->operandStack->popInt();
        Object* arrayref = executor->frame->operandStack->popRef();

        // TODO

    }
};

}