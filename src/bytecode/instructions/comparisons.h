/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/comparisons.h
 * \brief Comparisons: lcmp, fcmp, dcmp, if, if_icmp, if_acmp
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_COMPARISONS_H_
#define SRC_BYTECODE_INSTRUCTIONS_COMPARISONS_H_

#include <cmath>

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief lcmp instruction. */
class Inst_lcmp : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief fcmp instruction (fcmpl, fcmpg).
 * Use a is_g flag to determine whether it is fcmpl or fcmpg.
 */
class Inst_fcmp : public InstWithoutOperand {
 private:
  bool is_g_;

 public:
  Inst_fcmp(bool is_g) : is_g_(is_g) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief dcmp instruction (dcmpl, dcmpg).
 * Use a is_g flag to determine whether it is dcmpl or dcmpg.
 */
class Inst_dcmp : public InstWithoutOperand {
 private:
  bool is_g_;

 public:
  Inst_dcmp(bool is_g) : is_g_(is_g) {}

  void accept(FrameExecutor* executor);
};

/*! \brief Enum type of comparison operators. */
enum CmpOp { EQ, NE, LT, GE, GT, LE };

/*!
 * \brief if instruction (ifeq, ifne, iflt, ifge, ifgt, ifle).
 * Use op to identify different comparsions.
 */
class Inst_if : public InstWithOffset {
 private:
  CmpOp op_;

 public:
  Inst_if(CmpOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief if_icmp instruction (if_icmpeq, if_icmpne, if_icmplt, if_icmpge,
 * if_icmpgt, if_icmple).
 * Use op to identify different comparisons.
 */
class Inst_if_icmp : public InstWithOffset {
 private:
  CmpOp op_;

 public:
  Inst_if_icmp(CmpOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief if_acmp instruction (if_icmpeq, if_icmpne).
 * Use op to identify different comparisons.
 */
class Inst_if_acmp : public InstWithOffset {
 private:
  CmpOp op_;

 public:
  Inst_if_acmp(CmpOp op) : op_(op) {}

  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_COMPARISONS_H_
