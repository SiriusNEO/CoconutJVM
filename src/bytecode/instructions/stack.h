/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/stack.h
 * \brief Stack: pop, dup, swap
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_STACK_H_
#define SRC_BYTECODE_INSTRUCTIONS_STACK_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*!
 * \brief pop instruction (pop, pop2). Pop the stack.
 * Use is_two flag to indicate whehter it is a pop2.
 */
class Inst_pop : public InstWithoutOperand {
 private:
  bool is_two_;

 public:
  Inst_pop(bool is_two) : is_two_(is_two) {}

  void accept(FrameExecutor* executor);
};

/*!
 * \brief dup instruction. Duplicate the top of the stack.
 */
class Inst_dup : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief dup_x1 instruction. Duplicate the top operand stack value and insert
 * two values down.
 */
class Inst_dup_x1 : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief dup_x2 instruction. Duplicate the top operand stack value and insert
 * two or three values down.
 *
 * \note This instruction has two forms.
 *   Form1: ..., value3, value2, value1 ->
 *          ..., value1, value2, value3, value1
 *   Form2: ..., value2, value1 ->
 *          ..., value1, value2, value1
 * Here we take Form1.
 */
class Inst_dup_x2 : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief dup2 instruction. Duplicate the top one or two operand stack values.
 *
 * \note This instruction has two forms.
 *   Form1: ..., value2, value1 ->
 *          ..., value2, value1, value2, value1
 *   Form2: ..., value ->
 *          ..., value, value (same as dup)
 * Here we take Form1.
 */
class Inst_dup2 : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief dup2_x1 instruction. Duplicate the top one or two operand stack values
 * and insert two or three values down.
 *
 * \note This instruction has two forms.
 *   Form1: ..., value3, value2, value1 ->
 *          ..., value2, value1, value3, value2, value1
 *   Form2: ..., value2, value1 ->
 *          ..., value1, value2, value1
 * Here we take Form1.
 */
class Inst_dup2_x1 : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief dup2_x2 instruction. Duplicate the top one or two operand stack values
 * and insert two, three, or four values down.
 *
 * \note This instruction has two forms.
 *   Form1: ..., value4, value3, value2, value1 ->
 *          ..., value2, value1, value4, value3, value2, value1
 *   Form2: ..., value3, value2, value1 ->
 *          ..., value1, value3, value2, value1
 * Here we take Form1.
 */
class Inst_dup2_x2 : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief swap instruction. Swap the toppest two slots in the stack.
 */
class Inst_swap : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_STACK_H_
