/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/stores.h
 * \brief Stores: istore, lstore, fstore, dstore, astore, iastore, lastore,
 * fastore, dastore, aastore, bastore, castore, sastore
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_STORES_H_
#define SRC_BYTECODE_INSTRUCTIONS_STORES_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief istore instruction. Pop an Int from OS and store it in LVT. */
class Inst_istore : public InstWithIndex {
 public:
  Inst_istore(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief lstore instruction. Pop a Long from OS and store it in LVT. */
class Inst_lstore : public InstWithIndex {
 public:
  Inst_lstore(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief fstore instruction. Pop a Float from OS and store it in LVT. */
class Inst_fstore : public InstWithIndex {
 public:
  Inst_fstore(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief dstore instruction. Pop a Double from OS and store it in LVT. */
class Inst_dstore : public InstWithIndex {
 public:
  Inst_dstore(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief astore instruction. Pop an Array from OS and store it in LVT. */
class Inst_astore : public InstWithIndex {
 public:
  Inst_astore(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief iastore instruction. Pop an Array, get an element in the array from
 * OS and store it in LVT. */
class Inst_iastore : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_STORES_H_
