/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/comparisons.cc
 * \brief Implementation of comparisons.h
 * \author SiriusNEO
 */

#include "comparisons.h"

namespace coconut {

namespace bytecode {

void Inst_lcmp::accept(FrameExecutor* executor) {
  long long value1 = executor->frame->operandStack->popLong(),
            value2 = executor->frame->operandStack->popLong();
  if (value1 == value2)
    executor->frame->operandStack->pushInt(0);
  else if (value1 < value2)
    executor->frame->operandStack->pushInt(-1);
  else
    executor->frame->operandStack->pushInt(1);
}

void Inst_fcmp::accept(FrameExecutor* executor) {
  float value1 = executor->frame->operandStack->popFloat(),
        value2 = executor->frame->operandStack->popFloat();

  // IEEE 754
  // C++ operators may not follow, so check by hand
  if (std::isnan(value1) || std::isnan(value2)) {
    if (is_g_)
      executor->frame->operandStack->pushInt(1);
    else
      executor->frame->operandStack->pushInt(-1);
  } else {
    if (value1 == value2)
      executor->frame->operandStack->pushInt(0);
    else if (value1 < value2)
      executor->frame->operandStack->pushInt(-1);
    else
      executor->frame->operandStack->pushInt(1);
  }
}

void Inst_dcmp::accept(FrameExecutor* executor) {
  double value1 = executor->frame->operandStack->popDouble(),
         value2 = executor->frame->operandStack->popDouble();

  // IEEE 754
  // C++ operators may not follow, so check by hand
  if (std::isnan(value1) || std::isnan(value2)) {
    if (is_g_)
      executor->frame->operandStack->pushInt(1);
    else
      executor->frame->operandStack->pushInt(-1);
  } else {
    if (value1 == value2)
      executor->frame->operandStack->pushInt(0);
    else if (value1 < value2)
      executor->frame->operandStack->pushInt(-1);
    else
      executor->frame->operandStack->pushInt(1);
  }
}

void Inst_if::accept(FrameExecutor* executor) {
  int value = executor->frame->operandStack->popInt();
  bool succeed = false;

  switch (op_) {
    case EQ:
      succeed = (value == 0);
      break;
    case NE:
      succeed = (value != 0);
      break;
    case LT:
      succeed = (value < 0);
      break;
    case GE:
      succeed = (value >= 0);
      break;
    case GT:
      succeed = (value > 0);
      break;
    case LE:
      succeed = (value <= 0);
      break;
  }

  if (succeed) {
    executor->branch(offset);
  }
}

void Inst_if_icmp::accept(FrameExecutor* executor) {
  int value2 = executor->frame->operandStack->popInt(),
      value1 = executor->frame->operandStack->popInt();
  bool succeed = false;

  switch (op_) {
    case EQ:
      succeed = (value1 == value2);
      break;
    case NE:
      succeed = (value1 != value2);
      break;
    case LT:
      succeed = (value1 < value2);
      break;
    case GE:
      succeed = (value1 >= value2);
      break;
    case GT:
      succeed = (value1 > value2);
      break;
    case LE:
      succeed = (value1 <= value2);
      break;
  }

  if (succeed) {
    executor->branch(offset);
  }
}

void Inst_if_acmp::accept(FrameExecutor* executor) {
  rtda::Object *value2 = executor->frame->operandStack->popRef(),
               *value1 = executor->frame->operandStack->popRef();
  bool succeed = false;

  switch (op_) {
    case EQ:
      succeed = (value1 == value2);
      break;
    case NE:
      succeed = (value1 != value2);
      break;
    default: /* not possible */
      LOG(FATAL) << "if_acmp can not have operator type: " << op_;
      break;
  }

  if (succeed) {
    executor->branch(offset);
  }
}

}  // namespace bytecode

}  // namespace coconut
