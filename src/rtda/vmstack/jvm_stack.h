/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/jvm_stack.h
 * \brief jvm_stack.h file
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_VMSTACK_JVM_STACK_H_
#define SRC_RTDA_VMSTACK_JVM_STACK_H_

#include "local_variable_table.h"
#include "operand_stack.h"

namespace coconut {

namespace rtda {

// pre-declare JVMStack to avoid cycle reference.
class JVMStack;

/*!
 * \brief Frame of JVM stack.
 *
 * A frame contains a table of local variables (LVT) and the operand stack (OS)
 * in this context.
 */
class StackFrame {
 public:
  /*! \brief The pointer to the local variable table (LVT). */
  LocalVariableTable* localVariableTable;

  /*! \brief The pointer to the operand stack (OS). */
  OperandStack* operandStack;

  /*!
   * \brief Indicating next PC (Program Counter) of current frame.
   * \note This is owned by the frame. And the PC field is in the Thread.
   */
  int nextPc;

  /*!
   * \brief Default constructor.
   * \param maxLocals Max number of local variables.
   * \param maxStack Max space for the operand stack.
   * \param _lowerFrame The lower (next) frame.
   */
  StackFrame(unsigned int maxLocals, unsigned int maxStack,
             StackFrame* _lowerFrame)
      : nextPc(0), lowerFrame(_lowerFrame) {
    localVariableTable = new LocalVariableTable(maxLocals);
    operandStack = new OperandStack(maxStack);
  }

  /*! \brief Default destructor. */
  ~StackFrame() {
    if (localVariableTable != nullptr) {
      delete localVariableTable;
    }
    if (operandStack != nullptr) {
      delete operandStack;
    }
  }

  // Declare JVMStack as its friend class to let it access lowerFrame.
  friend JVMStack;

 private:
  /*!
   * \brief The lower (next) frame in the stack.
   *
   * The lowest frame is the one pushed to the stack firstly.
   * Use this pointer because JVMStack is organized as a linked list. This is
   * to prevent the VM from allocating all memory at first (allocate when
   * using).
   */
  StackFrame* lowerFrame;
};

/*!
 * \brief JVM stack.
 *
 * It is a linked list. The memory of its frame is allocated when pushed (so it
 * uses the arguments "maxLocals" and "maxStack" to perfrom the "push" action).
 * And delete the memory when pop.
 */
class JVMStack {
 private:
  /*! \brief The total capacity of the stack (the number of frames). */
  unsigned int capacity_;

 public:
  /*! \brief The current size of the stack (also the number of frames). */
  unsigned int size;

  /*! \brief The top frame (the one pushed into this stack lastly). */
  StackFrame* topFrame;

  /*!
   * \brief Default constructor.
   * \param capacity The capacity.
   */
  JVMStack(unsigned int capacity)
      : capacity_(capacity), size(0), topFrame(nullptr) {}

  /*! \brief Default destructor. */
  ~JVMStack() { clear(); }

  /*!
   * \brief Check whether the stack is empty.
   * \return Whether the stack is empty.
   */
  bool isEmpty() const { return topFrame == nullptr; }

  /*! \brief Clear the stack (pop all). */
  void clear() {
    while (!isEmpty()) {
      pop();
    }
  }

  /*!
   * \brief Push a frame into the stack.
   * \note We require the user pass arguments of its constructor instead of the
   * constructed frame because we want to manage the memory in this class.
   * \param maxLocals Max number of local variables.
   * \param maxStack Max space for the operand stack.
   */
  void push(unsigned int maxLocals, unsigned int maxStack);

  /*!
   * \brief Pop the top frame.
   * \note Pop will destruct the frame automatically.
   * \throw Panic if the stack is already empty.
   */
  void pop();
};

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_VMSTACK_JVM_STACK_H_
