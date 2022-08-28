/*
 *  Stores:
 *    istore, lstore, fstore, dstore, astore, iastore, lastore, fastore, dastore, aastore, bastore, castore, sastore
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

struct INS_istore: public InstWithIndex {

    INS_istore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setInt(
            index, executor->frame->operandStack->popInt()
        );
    }
};

struct INS_lstore: public InstWithIndex {

    INS_lstore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setLong(
            index, executor->frame->operandStack->popLong()
        );
    }
};

struct INS_fstore: public InstWithIndex {

    INS_fstore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setFloat(
            index, executor->frame->operandStack->popFloat()
        );
    }
};

struct INS_dstore: public InstWithIndex {

    INS_dstore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setDouble(
            index, executor->frame->operandStack->popDouble()
        );
    }
};

struct INS_astore: public InstWithIndex {

    INS_astore(unsigned int _index, bool _preset): InstWithIndex(_index, _preset) {}

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setRef(
            index, executor->frame->operandStack->popRef()
        );
    }
};

struct INS_iastore: public InstWithoutOperand {

    void accept(FrameExecutor* executor) {
        int value = executor->frame->operandStack->popInt();
        int index = executor->frame->operandStack->popInt();
        Object* arrayref = executor->frame->operandStack->popRef();

        // TODO

    }
};

}