/*
 *  Math:
 *    iadd, ladd, fadd, dadd,
 *    isub, lsub, fsub, dsub,
 *    imul, lmul, fmul, dmul,
 *    idiv, ldiv, fdiv, ddiv,
 *    irem, lrem, frem, drem,
 *    ineg, lneg, fneg, dneg,
 *    ishl, lshl, ishr, lshr, iushr, lushr,
 *    iand, land, ior, lor, ixor, lxor,
 *    iinc
 */

#pragma once


#include "../Instruction.hpp"

namespace coconut {

enum ArithmOp {ADD, SUB, MUL, DIV, REM, NEG, SHL, SHR, USHR, AND, OR, XOR};


struct INS_iarith: public InstWithoutOperand {
    ArithmOp op;

    INS_iarith(ArithmOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        int value1 = executor->frame->operandStack->popInt();
        int result;
        
        if (op == NEG) {
            result = -value1;
        }
        else {
            int value2 = executor->frame->operandStack->popInt();
            switch (op) {
                case ADD: result = value1 + value2; break;
                case SUB: result = value1 - value2; break;
                case MUL: result = value1 * value2; break;
                case DIV: case REM: {
                    if (value2 == 0) {
                        panic("java.lang.ArithmeticException: / by zero");
                    }
                    if (op == DIV) result = value1 / value2; 
                    else result = value1 % value2;
                    break;
                }
                case SHL: result = value1 << (value2 & 0x1f); break;
                case SHR: result = value1 >> ((unsigned int)(value2 & 0x1f)); break;
                case USHR: result = (unsigned int)(value1) >> ((unsigned int)(value2 & 0x1f)); break;
                case AND: result = value1 & value2; break;
                case OR: result = value1 | value2; break;
                case XOR: result = value1 ^ value2; break;
                case NEG: /* impossible */ break;
            }
        }

        executor->frame->operandStack->pushInt(result);
    }
};

}
