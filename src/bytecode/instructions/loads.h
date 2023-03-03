/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/loads.h
 * \brief Loads: iload, lload, fload, dload, aload, iaload, laload, faload,
 * daload, aaload, baload, caload, saload
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_LOADS_H_
#define SRC_BYTECODE_INSTRUCTIONS_LOADS_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief iload instruction. Load an Int from LVT and push it to OS. */
class Inst_iload : public InstWithIndex {
 public:
  Inst_iload(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief lload instruction. Load a Long from LVT and push it to OS. */
class Inst_lload : public InstWithIndex {
 public:
  Inst_lload(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief fload instruction. Load a Float from LVT and push it to OS. */
class Inst_fload : public InstWithIndex {
 public:
  Inst_fload(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief iload instruction. Load a Double from LVT and push it to OS. */
class Inst_dload : public InstWithIndex {
 public:
  Inst_dload(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief aload instruction. Load an Array from LVT and push it to OS. */
class Inst_aload : public InstWithIndex {
 public:
  Inst_aload(unsigned int index, bool preset) : InstWithIndex(index, preset) {}

  void accept(FrameExecutor* executor);
};

/*! \brief iaload instruction. Load an element in an Array from LVT and push it
 * to OS. */
class Inst_iaload : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_LOADS_H_
