/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/bytecode_decoder.h
 * \brief Java bytecode decoder.
 * \author SiriusNEO
 */

#include "inst_base.h"

#ifndef SRC_BYTECODE_BYTECODE_DECODER_H_
#define SRC_BYTECODE_BYTECODE_DECODER_H_

namespace coconut {

namespace bytecode {

/*!
 * \brief Java bytecode decoder. Decode instructions in the form of bytes to
 * representation in JVM.
 *
 * It can: 1. decode instructions by opcode.  2. fetch operands.
 */
class BytecodeDecoder {
 public:
  /*! \brief The reader of the decoder. */
  utils::ByteReader reader;

  /*!
   * \brief Default constructor.
   * \param codeLen The length of the code.
   * \param code The code, in the form of bytes stream.
   */
  BytecodeDecoder(size_t codeLen, BYTE* code) : reader(codeLen, code) {}

  /*!
   * \brief Fetch a new instruction from the memory pool (from the reader).
   * \return The constructed instruction.
   */
  Instruction* getInst() { return instructionFactory(reader.fetchU1()); }

  /*!
   * \brief Get the operands for an instruction.
   * \param inst The pointer of the instruction.
   */
  void getOperands(Instruction* inst) { inst->accept(&this->reader); }

  /*!
   * \brief The factory of Java bytecode instructions. Make instructions
   * according to the opcode.
   * \param opcode The opcode (Forms) of the instruction.
   * \return The pointer of the created instruction.
   * \note This method allocate new memory for the instruction. User should
   * delete it manually.
   */
  Instruction* instructionFactory(uint8_t opcode);
};

}  // namespace bytecode

}  // namespace coconut

#endif  // SRC_BYTECODE_BYTECODE_DECODER_H_
