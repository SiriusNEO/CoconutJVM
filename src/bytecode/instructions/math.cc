/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/math.cc
 * \brief Implementation of math.h
 * \author SiriusNEO
 */

#include "math.h"

namespace coconut {

namespace bytecode {

void Inst_iarith::accept(FrameExecutor* executor) {
  int value2 = executor->frame->operandStack->popInt();
  int result;

  if (op_ == NEG) {
    result = -value2;
  } else {
    int value1 = executor->frame->operandStack->popInt();
    switch (op_) {
      case ADD:
        result = value1 + value2;
        break;
      case SUB:
        result = value1 - value2;
        break;
      case MUL:
        result = value1 * value2;
        break;
      case DIV:
      case REM: {
        // TODO: throw Java Exception instead.
        CHECK(value2 != 0) << "java.lang.ArithmeticException: / by zero";
        if (op_ == DIV)
          result = value1 / value2;
        else
          result = value1 % value2;
        break;
      }
      case SHL:
        result = value1 << (value2 & 0x1f);
        break;
      case SHR:
        result = value1 >> ((unsigned int)(value2 & 0x1f));
        break;
      case USHR:
        result = (unsigned int)(value1) >> ((unsigned int)(value2 & 0x1f));
        break;
      case AND:
        result = value1 & value2;
        break;
      case OR:
        result = value1 | value2;
        break;
      case XOR:
        result = value1 ^ value2;
        break;
      case NEG: /* impossible */
        break;
    }
  }

  executor->frame->operandStack->pushInt(result);
}

void Inst_larith::accept(FrameExecutor* executor) {
  long long value2 = executor->frame->operandStack->popLong();
  long long result;

  if (op_ == NEG) {
    result = -value2;
  } else {
    long long value1 = executor->frame->operandStack->popLong();
    switch (op_) {
      case ADD:
        result = value1 + value2;
        break;
      case SUB:
        result = value1 - value2;
        break;
      case MUL:
        result = value1 * value2;
        break;
      case DIV:
      case REM: {
        // TODO: throw Java Exception instead.
        CHECK(value2 != 0) << "java.lang.ArithmeticException: / by zero";
        if (op_ == DIV)
          result = value1 / value2;
        else
          result = value1 % value2;
        break;
      }
      case SHL:
        result = value1 << (value2 & 0x3f);
        break;
      case SHR:
        result = value1 >> ((unsigned long long)(value2 & 0x3f));
        break;
      case USHR:
        result = (unsigned long long)(value1) >>
                 ((unsigned long long)(value2 & 0x3f));
        break;
      case AND:
        result = value1 & value2;
        break;
      case OR:
        result = value1 | value2;
        break;
      case XOR:
        result = value1 ^ value2;
        break;
      case NEG: /* impossible */
        break;
    }
  }

  executor->frame->operandStack->pushLong(result);
}

void Inst_farith::accept(FrameExecutor* executor) {
  float value2 = executor->frame->operandStack->popFloat();
  float result;

  if (op_ == NEG) {
    result = -value2;
  } else {
    float value1 = executor->frame->operandStack->popFloat();
    switch (op_) {
      case ADD:
        result = value1 + value2;
        break;
      case SUB:
        result = value1 - value2;
        break;
      case MUL:
        result = value1 * value2;
        break;
      case DIV:
      case REM: {
        if (op_ == DIV)
          result = value1 / value2;
        else
          result = std::fmod(value1, value2);  // check
        break;
      }
      case SHL:
      case SHR:
      case USHR:
      case AND:
      case OR:
      case XOR:
      case NEG: /* impossible */
        break;
    }
  }

  executor->frame->operandStack->pushFloat(result);
}

void Inst_darith::accept(FrameExecutor* executor) {
  double value2 = executor->frame->operandStack->popDouble();
  double result;

  if (op_ == NEG) {
    result = -value2;
  } else {
    double value1 = executor->frame->operandStack->popDouble();
    switch (op_) {
      case ADD:
        result = value1 + value2;
        break;
      case SUB:
        result = value1 - value2;
        break;
      case MUL:
        result = value1 * value2;
        break;
      case DIV:
      case REM: {
        if (op_ == DIV)
          result = value1 / value2;
        else
          result = std::fmod(value1, value2);  // check
        break;
      }
      case SHL:
      case SHR:
      case USHR:
      case AND:
      case OR:
      case XOR:
      case NEG: /* impossible */
        break;
    }
  }

  executor->frame->operandStack->pushDouble(result);
}

void Inst_iinc::accept(utils::ByteReader* reader) {
  index_ = (unsigned int)(reader->fetchU1());
  imm_ = int(reader->fetchInt8());
}

void Inst_iinc::accept(FrameExecutor* executor) {
  executor->frame->localVariableTable->setInt(
      index_, executor->frame->localVariableTable->getInt(index_) + imm_);
}

}  // namespace bytecode

}  // namespace coconut
