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

namespace coconut {

Instruction* BytecodeDecoder::instructionFactory(uint8_t opcode) {
    switch (opcode) {
        case 0x00:  return new Inst_nop();
        case 0x01:  return new Inst_aconst_null();
        default: panic("jvm decode error");
    }

    // to eliminate warning
    return nullptr;
}

}