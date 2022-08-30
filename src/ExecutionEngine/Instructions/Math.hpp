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
#include <cmath>

namespace coconut {

enum ArithmOp {ADD, SUB, MUL, DIV, REM, NEG, SHL, SHR, USHR, AND, OR, XOR};


struct Inst_iarith: public InstWithoutOperand {
    ArithmOp op;

    Inst_iarith(ArithmOp _op): op(_op) {}

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

struct Inst_larith: public InstWithoutOperand {
    ArithmOp op;

    Inst_larith(ArithmOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        long long value1 = executor->frame->operandStack->popLong();
        long long result;
        
        if (op == NEG) {
            result = -value1;
        }
        else {
            long long value2 = executor->frame->operandStack->popLong();
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
                case SHL: result = value1 << (value2 & 0x3f); break;
                case SHR: result = value1 >> ((unsigned long long)(value2 & 0x3f)); break;
                case USHR: result = (unsigned long long)(value1) >> ((unsigned long long)(value2 & 0x3f)); break;
                case AND: result = value1 & value2; break;
                case OR: result = value1 | value2; break;
                case XOR: result = value1 ^ value2; break;
                case NEG: /* impossible */ break;
            }
        }

        executor->frame->operandStack->pushLong(result);
    }
};

struct Inst_farith: public InstWithoutOperand {
    ArithmOp op;

    Inst_farith(ArithmOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        float value1 = executor->frame->operandStack->popFloat();
        float result;
        
        if (op == NEG) {
            result = -value1;
        }
        else {
            float value2 = executor->frame->operandStack->popFloat();
            switch (op) {
                case ADD: result = value1 + value2; break;
                case SUB: result = value1 - value2; break;
                case MUL: result = value1 * value2; break;
                case DIV: case REM: {
                    if (op == DIV) result = value1 / value2; 
                    else result = std::fmod(value1, value2); // check
                    break;
                }
                case SHL:case SHR:case USHR:case AND:case OR:case XOR:case NEG: /* impossible */ break;
            }
        }

        executor->frame->operandStack->pushFloat(result);
    }
};

struct Inst_darith: public InstWithoutOperand {
    ArithmOp op;

    Inst_darith(ArithmOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        double value1 = executor->frame->operandStack->popDouble();
        double result;
        
        if (op == NEG) {
            result = -value1;
        }
        else {
            double value2 = executor->frame->operandStack->popDouble();
            switch (op) {
                case ADD: result = value1 + value2; break;
                case SUB: result = value1 - value2; break;
                case MUL: result = value1 * value2; break;
                case DIV: case REM: {
                    if (op == DIV) result = value1 / value2; 
                    else result = std::fmod(value1, value2); // check
                    break;
                }
                case SHL:case SHR:case USHR:case AND:case OR:case XOR:case NEG: /* impossible */ break;
            }
        }

        executor->frame->operandStack->pushDouble(result);
    }
};

struct Inst_iinc: public Instruction {
    unsigned int index;
    int imm;

    void accept(ByteReader* reader) {
        index = (unsigned int)(reader->fetchU1());
        imm   = int(reader->fetchInt8());
    }

    void accept(FrameExecutor* executor) {
        executor->frame->localVariableTable->setInt(
            index, executor->frame->localVariableTable->getInt(index) + imm
        );
    }
};

}
