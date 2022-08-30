/*
 *  Stores:
 *    istore, lstore, fstore, dstore, astore, iastore, lastore, fastore, dastore, aastore, bastore, castore, sastore
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct Inst_istore: public InstWithIndex {

    Inst_istore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setInt(
            index, executor->frame->operandStack->popInt()
        );
    }
};

struct Inst_lstore: public InstWithIndex {

    Inst_lstore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setLong(
            index, executor->frame->operandStack->popLong()
        );
    }
};

struct Inst_fstore: public InstWithIndex {

    Inst_fstore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setFloat(
            index, executor->frame->operandStack->popFloat()
        );
    }
};

struct Inst_dstore: public InstWithIndex {

    Inst_dstore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setDouble(
            index, executor->frame->operandStack->popDouble()
        );
    }
};

struct Inst_astore: public InstWithIndex {

    Inst_astore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setRef(
            index, executor->frame->operandStack->popRef()
        );
    }
};

struct Inst_iastore: public InstWithoutOperand {

    void accept(FrameExecutor* executor) {
        int value = executor->frame->operandStack->popInt();
        int index = executor->frame->operandStack->popInt();
        Object* arrayref = executor->frame->operandStack->popRef();

        // TODO

    }
};

}