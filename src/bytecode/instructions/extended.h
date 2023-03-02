/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/extended.h
 * \brief Extented: wide, multianewarray, ifnull, ifnonnull, goto_w, jsr_w
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_EXTENDED_H_
#define SRC_BYTECODE_INSTRUCTIONS_EXTENDED_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*!
 * \brief wide instruction.
 *
 * Extend local variable index by additional bytes. It modifies the behavior of
 * another instruction (So when reading wide, we will continue to read the
 * instruction followed in the byte stream and store it in modified). It is more
 * like a "decorator" instruction.
 */
class Inst_wide : public Instruction {
 private:
  Instruction* modified_;

 public:
  Inst_wide(Instruction* modified) : modified_(modified) {}

  ~Inst_wide() { delete modified_; }

  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

/*! \brief ifnull instruction. Jump if null. */
class Inst_ifnull : public InstWithOffset {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief ifnonnull instruction. Jump if non null. */
class Inst_ifnonnull : public InstWithOffset {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief goto_w instruction. Wide index version of goto (4 bytes). */
class Inst_goto_w : public Instruction {
 private:
  int offset_;

 public:
  void accept(utils::ByteReader* reader);

  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_EXTENDED_H_
