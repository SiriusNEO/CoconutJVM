/*
 *  Comparisons:
 *    lcmp, fcmp, dcmp, if, if_icmp, if_acmp
 */

#pragma once


#include "../Instruction.hpp"
#include <cmath>

namespace coconut {

struct Inst_lcmp: public InstWitoutOperand {
    void accept(FrameExecutor* executor) {
        long long value1 = executor->frame->operandStack->popLong(), 
                  value2 = executor->frame->operandStack->popLong();
        if (value1 == value2) executor->frame->operandStack->pushInt(0);
        else if (value1 < value2) executor->frame->operandStack->pushInt(-1);
        else executor->frame->operandStack->pushInt(1);
    }
};

struct Inst_fcmp: public InstWitoutOperand {
    bool is_g;

    Inst_fcmp(bool _is_g) : is_g(_is_g) {}

    void accept(FrameExecutor* executor) {
        float value1 = executor->frame->operandStack->popFloat(), 
              value2 = executor->frame->operandStack->popFloat();

        // IEEE 754
        // C++ operators may not follow, so check by hand
        if (std::isnan(value1) || std::isnan(value2)) {
            if (is_g) executor->frame->operandStack->pushInt(1);
            else executor->frame->operandStack->pushInt(-1);
        }
        else {
            if (value1 == value2) executor->frame->operandStack->pushInt(0);
            else if (value1 < value2) executor->frame->operandStack->pushInt(-1);
            else executor->frame->operandStack->pushInt(1);
        }
    }
};

struct Inst_dcmp: public InstWitoutOperand {
    bool is_g;

    Inst_dcmp(bool _is_g) : is_g(_is_g) {}

    void accept(FrameExecutor* executor) {
        double value1 = executor->frame->operandStack->popDouble(), 
               value2 = executor->frame->operandStack->popDouble();

        // IEEE 754
        // C++ operators may not follow, so check by hand
        if (std::isnan(value1) || std::isnan(value2)) {
            if (is_g) executor->frame->operandStack->pushInt(1);
            else executor->frame->operandStack->pushInt(-1);
        }
        else {
            if (value1 == value2) executor->frame->operandStack->pushInt(0);
            else if (value1 < value2) executor->frame->operandStack->pushInt(-1);
            else executor->frame->operandStack->pushInt(1);
        }
    }
};

enum CmpOp {eq, ne, lt, ge, gt, le};

struct Inst_if: public InstWithOffset {
    CmpOp op;

    Inst_if(CmpOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        int value = executor->frame->operandStack->popInt();
        bool succeed = false;

        switch (op) {
            case eq: succeed = (value == 0); break;
            case ne: succeed = (value != 0); break;
            case lt: succeed = (value < 0); break;
            case ge: succeed = (value >= 0); break;
            case gt: succeed = (value > 0); break;
            case le: succeed = (value <= 0); break;
        }

        if (succeed) {
            executor->branch(offset);
        }
    }
};

struct Inst_if_icmp: public InstWithOffset {
    CmpOp op;

    Inst_if_icmp(CmpOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        int value1 = executor->frame->operandStack->popInt(),
            value2 = executor->frame->operandStack->popInt();
        bool succeed = false;

        switch (op) {
            case eq: succeed = (value1 == value2); break;
            case ne: succeed = (value1 != value2); break;
            case lt: succeed = (value1 < value2); break;
            case ge: succeed = (value1 >= value2); break;
            case gt: succeed = (value1 > value2); break;
            case le: succeed = (value1 <= value2); break;
        }

        if (succeed) {
            executor->branch(offset);
        }
    }
};

struct Inst_if_acmp: public InstWithOffset {
    CmpOp op;

    Inst_if_acmp(CmpOp _op): op(_op) {}

    void accept(FrameExecutor* executor) {
        Object *value1 = executor->frame->operandStack->popRef(),
               *value2 = executor->frame->operandStack->popRef();
        bool succeed = false;

        switch (op) {
            case eq: succeed = (value1 == value2); break;
            case ne: succeed = (value1 != value2); break;
            default: /*not appear*/ break;
        }

        if (succeed) {
            executor->branch(offset);
        }
    }
};

}