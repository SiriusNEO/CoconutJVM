/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/constants.h
 * \brief Constants: nop, aconst_null, iconst, lconst, fconst, dconst, bipush,
 * sipush, ldc
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_CONSTANTS_H_
#define SRC_BYTECODE_INSTRUCTIONS_CONSTANTS_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief nop instruction. */
class Inst_nop : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief aconst_null instruction. */
class Inst_aconst_null : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief iconst instruction.
 * Use val to indicate iconst_x. Note that iconst_ml is treated as iconst_(-1).
 */
class Inst_iconst : public InstWithoutOperand {
 private:
  int val_;

 public:
  Inst_iconst(int val) : val_(val) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief lconst instruction.
 * Use val to indicate lconst_x.
 */
class Inst_lconst : public InstWithoutOperand {
 private:
  long long val_;

 public:
  Inst_lconst(long long val) : val_(val) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief fconst instruction.
 * Use val to indicate lconst_x.
 */
class Inst_fconst : public InstWithoutOperand {
 private:
  float val_;

 public:
  Inst_fconst(float val) : val_(val) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief dconst instruction.
 * Use val to indicate lconst_x.
 */
class Inst_dconst : public InstWithoutOperand {
 private:
  double val_;

 public:
  Inst_dconst(double val) : val_(val) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief bipush instruction (push byte).
 * It has an immediate value (1 byte). The immediate byte is sign-extended to an
 * int value.
 */
class Inst_bipush : public Instruction {
 private:
  int imm_;

 public:
  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

/*!
 * \brief sipush instruction (push short).
 * It has an immediate value (2 bytes). The immediate value is sign-extended to
 * an int value.
 */
class Inst_sipush : public Instruction {
 private:
  int imm_;

 public:
  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_CONSTANTS_H_
