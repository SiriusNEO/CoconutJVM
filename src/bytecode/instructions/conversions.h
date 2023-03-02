/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/instructions/conversions.h
 * \brief Conversions: i2b, i2c, i2s, i2f, i2l, i2d,
 *    l2i, l2f, l2d,
 *    f2i, f2l, f2d,
 *    d2i, d2l, d2f
 * \author SiriusNEO
 */

#ifndef SRC_BYTECODE_INSTRUCTIONS_CONVERSIONS_H_
#define SRC_BYTECODE_INSTRUCTIONS_CONVERSIONS_H_

#include "../inst_base.h"

namespace coconut {

namespace bytecode {

/*! \brief i2b instruction (int to byte). */
class Inst_i2b : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief i2c instruction (int to char). */
class Inst_i2c : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief i2s instruction (int to short). */
class Inst_i2s : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief i2l instruction (int to long). */
class Inst_i2l : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief i2f instruction (int to float). */
class Inst_i2f : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief i2d instruction (int to double). */
class Inst_i2d : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief l2i instruction (long to int). */
class Inst_l2i : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief l2f instruction (long to float). */
class Inst_l2f : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief l2d instruction (long to double). */
class Inst_l2d : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief f2i instruction (float to int). */
class Inst_f2i : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief f2l instruction (float to long). */
class Inst_f2l : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief f2d instruction (float to double). */
class Inst_f2d : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief d2i instruction (double to int). */
class Inst_d2i : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief d2l instruction (double to long). */
class Inst_d2l : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

/*! \brief d2f instruction (double to float). */
class Inst_d2f : public InstWithoutOperand {
 public:
  void accept(FrameExecutor* executor);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_INSTRUCTIONS_CONVERSIONS_H_
