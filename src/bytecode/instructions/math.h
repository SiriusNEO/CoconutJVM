/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/math.h
 * \brief Math:
 *    iadd, ladd, fadd, dadd,
 *    isub, lsub, fsub, dsub,
 *    imul, lmul, fmul, dmul,
 *    idiv, ldiv, fdiv, ddiv,
 *    irem, lrem, frem, drem,
 *    ineg, lneg, fneg, dneg,
 *    ishl, lshl, ishr, lshr, iushr, lushr,
 *    iand, land, ior, lor, ixor, lxor,
 *    iinc
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_MATH_H_
#define SRC_BYTECODE_INSTRUCTIONS_MATH_H_

#include <cmath>

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief Enum type for arithmetic operators. */
enum ArithmOp { ADD, SUB, MUL, DIV, REM, NEG, SHL, SHR, USHR, AND, OR, XOR };

/*!
 * \brief iarith instruction (iadd, isub, imul, idiv, irem, ineg, ishl, ishr,
 * iushr, iand, ior, ixor).
 * Use op to identify different arithmetic operations.
 */
class Inst_iarith : public InstWithoutOperand {
 private:
  ArithmOp op_;

 public:
  Inst_iarith(ArithmOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief larith instruction (ladd, lsub, lmul, ldiv, lrem, lneg, lshl, lshr,
 * lushr, land, lor, lxor).
 * Use op to identify different arithmetic operations.
 */
class Inst_larith : public InstWithoutOperand {
 private:
  ArithmOp op_;

 public:
  Inst_larith(ArithmOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief farith instruction (fadd, fsub, fmul, fdiv, frem, fneg).
 * Use op to identify different arithmetic operations.
 */
class Inst_farith : public InstWithoutOperand {
 private:
  ArithmOp op_;

 public:
  Inst_farith(ArithmOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief darith instruction (dadd, dsub, dmul, ddiv, drem, dneg).
 * Use op to identify different arithmetic operations.
 */
class Inst_darith : public InstWithoutOperand {
 private:
  ArithmOp op_;

 public:
  Inst_darith(ArithmOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief iinc instruction.
 * Its reading way is special and it is only for int, so let it be a separate
 * class here.
 * It will make an increment (+imm) to the value whose position is marked by
 * "index" in the local variable table.
 */
class Inst_iinc : public Instruction {
 private:
  unsigned int index_;
  int imm_;

 public:
  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_MATH_H_
