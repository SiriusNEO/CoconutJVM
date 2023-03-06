/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/vm/interpreter.h
 * \brief Java Bytecode Interpreter.
 * \author SiriusNEO
 */

#ifndef SRC_VM_INTERPRETER_H_
#define SRC_VM_INTERPRETER_H_

#include "../bytecode/bytecode_decoder.h"
#include "../classloader/classfile.h"

namespace coconut {

namespace vm {

/*!
 * \brief Java Bytecode Interpreter.
 *
 * It interprets a method (in the form of MethodInfo) step by step. To be
 * detailed, it will create a new thread and push a single new stack frame to
 * the VM stack. Then all operations will be taken in this frame.
 *
 * TODO: iterate it.
 */
class Interpreter {
 private:
  /*! \brief Internal decoder. */
  bytecode::BytecodeDecoder* decoder_;

  /*!
   * \brief Loop in a thread. It is an infinite-loop for now.
   * \param thread The thread the interpreter runs.
   */
  void loop(rtda::Thread* thread);

 public:
  /*! \brief Default constructor. */
  Interpreter() : decoder_(nullptr) {}

  /*! \brief Internal destructor. */
  ~Interpreter() {
    if (decoder_ != nullptr) {
      delete decoder_;
    }
  }

  /*!
   * \brief Interpret a method.
   * \param  methodInfo The info of the method we want to interpret.
   */
  void interpret(classloader::MemberInfo& methodInfo);
};

}  // namespace vm

}  // namespace coconut

#endif  // SRC_VM_INTERPRETER_H_
