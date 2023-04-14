/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/operand_stack.h
 * \brief Operand Stack of JVM.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_VMSTACK_OPERAND_STACK_H_
#define SRC_RTDA_VMSTACK_OPERAND_STACK_H_

#include "../../utils/logging.h"
#include "../slot.h"

namespace coconut {

namespace rtda {

/*!
 * \brief Operand Stack of JVM.
 *
 * As we know, Java bytecode is a stacked execution language. Note that there
 * are two levels of stacks in JVM: the operand stack and the JVMStack (runtime
 * stack).
 * The operand stack is in a frame of the JVM Stack. It is used to perfrom a
 * stack-style execution. E.g. when we interpret an instruction, saying "add" in
 * JVM, we pop two operands from the operand stack, do addition and push the
 * result back to the stack.
 */
class OperandStack {
 private:
  /*! \brief Slots in the stack. */
  Slot* slots_;

  /*! \brief Top position of the stack. */
  unsigned int top_;

  /*! \brief Max number of slots in the stack. */
  unsigned int maxStack_;

  /*! \brief Stack up. */
  void up() {
    ++top_;
    CHECK(top_ <= maxStack_) << "OperandStack overflow!";
  }

  /*! \brief Stack down. */
  void down() {
    --top_;
    CHECK(top_ >= 0) << "OperandStack underflow!";
  }

 public:
  /*!
   * \brief Default constructor. Pre-allocate all spaces for an operand stack.
   * (Since it won't be too large in a single frame)
   * \param maxStack Max space for the operand stack.
   */
  OperandStack(unsigned int maxStack) : maxStack_(maxStack), top_(0) {
    slots_ = new Slot[maxStack];
  }

  /*! \brief Default destructor. */
  ~OperandStack() { delete[] slots_; }

  /*! \brief Show the brief info of the stack. */
  std::string brief();

  /*!
   * \brief Get a slot from a postion.
   * \param index The position we fetch the slot.
   */
  Slot getSlot(int index);

  /*!
   * \brief Push a slot into the stack.
   * \param slot The slot we want to push.
   */
  void pushSlot(Slot slot);

  /*!
   * \brief Pop a slot from the stack.
   * \return The slot popped.
   */
  Slot popSlot();

  /*!
   * \brief Push an integer(int32) into the stack.
   * \param val The value we want to push.
   */
  void pushInt(int val);

  /*!
   * \brief Pop an integer(int32) from the stack.
   * \return The value popped.
   */
  int popInt();

  /*!
   * \brief Push a float32 number into the stack.
   * \param val The value we want to push.
   */
  void pushFloat(float val);

  /*!
   * \brief Pop a float32 number from the stack.
   * \return The value popped.
   */
  float popFloat();

  /*!
   * \brief Push a long(int64) integer into the stack.
   * \param val The value we want to push.
   */
  void pushLong(long long val);

  /*!
   * \brief Pop a long(int64) integer from the stack.
   * \return The value popped.
   */
  long long popLong();

  /*!
   * \brief Push a double(float64) number into the stack.
   * \param val The value we want to push.
   */
  void pushDouble(double val);

  /*!
   * \brief Pop a double(float64) number from the stack.
   * \return The value popped.
   */
  double popDouble();

  /*!
   * \brief Push an Object reference into the stack.
   * \param ref The ref we want to push.
   */
  void pushRef(Object* ref);

  /*!
   * \brief Pop an Object reference from the stack.
   * \return The ref popped.
   */
  Object* popRef();
};

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_VMSTACK_OPERAND_STACK_H_
