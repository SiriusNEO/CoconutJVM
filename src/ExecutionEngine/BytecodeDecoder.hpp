/*
 *  Java Bytecode Decoder
 *  It can: 1. decode by opcode  2. fetch operands
 */

#include "Instruction.hpp"
#include "Instructions/Comparisons.hpp"
#include "Instructions/Constants.hpp"
#include "Instructions/Control.hpp"
#include "Instructions/Conversions.hpp"
#include "Instructions/Extended.hpp"
#include "Instructions/Loads.hpp"
#include "Instructions/Math.hpp"
#include "Instructions/References.hpp"
#include "Instructions/Reversed.hpp"
#include "Instructions/Stack.hpp"
#include "Instructions/Stores.hpp"


#pragma once

namespace coconut {

class BytecodeDecoder {
    public:
        ByteReader reader;

        BytecodeDecoder(size_t codeLen, BYTE* code): reader(codeLen, code) {}

        Instruction* getInst() {
            return instructionFactory(reader.fetchU1());
        }

        void getOperands(Instruction* inst) {
            inst->accept(&this->reader);
        }

        // call new. remember to delete
        static Instruction* instructionFactory(uint8_t opcode) {
            switch (opcode) {
                case 0x00:  return new Inst_nop();
                case 0x01:  return new Inst_aconst_null();
                default: panic("jvm decode error");
            }

            // to eliminate warning
            return nullptr;
        }
};

}