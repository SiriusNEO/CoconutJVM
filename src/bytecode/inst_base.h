/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/inst_base.h
 * \brief Base classes and wrappers for the Java bytecode instructions.
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INST_BASE_H_
#define SRC_BYTECODE_INST_BASE_H_

#include "../rtda/thread.h"
#include "../utils/byte_reader.h"
#include "../utils/typedef.h"

namespace coconut {

namespace bytecode {

// pre-declare FrameExecutor to avoid cycle reference.
class FrameExecutor;

/*!
 * \brief Base class of all types Java bytecode instructions.
 *
 * All Java bytecode instructions in this JVM are its subclasses.
 * The instruction can accept a ByteReader or a FrameExecutor. As for reader,
 * it will collect its information in byte stream; for the executor, it will
 * apply on this executor (do the actual execution).
 */
class Instruction {
 public:
  // Declared as virtual to let some special instructions be correctly deleted.
  virtual ~Instruction() {}

  /*!
   * \brief Accept a byte reader, to load the instruction.
   * \param reader the byte reader.
   */
  virtual void accept(utils::ByteReader* reader) = 0;

  /*!
   * \brief Accept a frame executor, to apply the instruction on this executor
   * (and its corresponding frame).
   * \param executor the frame executor.
   */
  virtual void accept(FrameExecutor* executor) = 0;
};

/*!
 * \brief A wrapper for a JVM Stack frame. Provide some interfaces for
 * executation.
 */
class FrameExecutor {
 private:
  /*! \brief Current thread. */
  rtda::Thread* thread;

 public:
  /*! \brief Current stack frame. */
  rtda::StackFrame* frame;

  FrameExecutor(rtda::Thread* _thread, rtda::StackFrame* _frame)
      : thread(_thread), frame(_frame) {}

  /*!
   * \brief Execute an instruction.
   * \param inst the instruction to be executed.
   */
  void execute(Instruction* inst) { inst->accept(this); }

  /*!
   * \brief Perform a branch action. That is, move the pc according to the
   * offset. \param offset the offset.
   */
  void branch(int offset) { frame->nextPc = thread->pc + offset; }
};

/*! \brief Base class for instructions without operands. */
class InstWithoutOperand : public Instruction {
 public:
  void accept(utils::ByteReader* reader) {
    // do nothing
  }
};

/*! \brief Base class for instructions with an int16 offset. */
class InstWithOffset : public Instruction {
 protected:
  int offset_;

 public:
  void accept(utils::ByteReader* reader) {
    offset_ = int(reader->fetchInt16());
  }
};

/*! \brief Base class for instructions with an uint32 index. */
class InstWithIndex : public Instruction {
 protected:
  unsigned int index_;
  bool preset_;

 public:
  InstWithIndex(unsigned int index, bool preset)
      : index_(index), preset_(preset) {
    // if _preset is true, arg _index is meaningless
  }

  void accept(utils::ByteReader* reader) {
    if (!preset_) {
      index_ = (unsigned int)(reader->fetchU1());
    }
  }
};

/*! \brief Base class for instructions with a wide index (uint64). */
class InstWithWideIndex : public Instruction {
 protected:
  unsigned int index_;

 public:
  void accept(utils::ByteReader* reader) {
    index_ = (unsigned int)(reader->fetchU2());
  }
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INST_BASE_H_
