/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/control.h
 * \brief Control: goto, jsr, ret, tableswitch, lookupswitch, ireturn, lreturn,
 * freturn, dreturn, areturn, return
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_CONTROL_H_
#define SRC_BYTECODE_INSTRUCTIONS_CONTROL_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief goto instruction. */
class Inst_goto : public InstWithOffset {
 public:
  void accept(FrameExecutor* executor);
};

/*!
 * \brief tableswitch instruction.
 *
 * Access jump table by index and jump. It has many jump targets (jump offsets).
 */
class Inst_tableswitch : public Instruction {
 private:
  int defaultOffset_, low_, high_;
  std::vector<int> jumpOffsets_;

 public:
  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

/*!
 * \brief lookupswitch instruction.
 *
 * Access jump table by key match and jump. It has many jump targets (stored in
 * key-value paris).
 */
class Inst_lookupswitch : public Instruction {
 private:
  int defaultOffset_, npairs_;
  std::vector<int> matchOffsetPairs_;

 public:
  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

// TODO: jsr, ret, xreturn implementation

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_CONTROL_H_
