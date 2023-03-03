/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/bytecode/bytecode_decoder.cc
 * \brief Implementation of bytecode_decoder.h
 * \author SiriusNEO
 */

#include "bytecode_decoder.h"

namespace coconut {

namespace bytecode {

Instruction* BytecodeDecoder::instructionFactory(uint8_t opcode) {
  // Good for debugging in hex format
  LOG(INFO) << "build inst: 0x" << std::hex << static_cast<unsigned int>(opcode)
            << std::dec;

  switch (opcode) {
    // Constants
    case 0x00:
      return new Inst_nop();
    case 0x01:
      return new Inst_aconst_null();
    case 0x02:
      return new Inst_iconst(-1);
    case 0x03:
      return new Inst_iconst(0);
    case 0x04:
      return new Inst_iconst(1);
    case 0x05:
      return new Inst_iconst(2);
    case 0x06:
      return new Inst_iconst(3);
    case 0x07:
      return new Inst_iconst(4);
    case 0x08:
      return new Inst_iconst(5);
    case 0x09:
      return new Inst_lconst(0);
    case 0x0a:
      return new Inst_lconst(1);
    case 0x0b:
      return new Inst_fconst(0);
    case 0x0c:
      return new Inst_fconst(1);
    case 0x0d:
      return new Inst_fconst(2);
    case 0x0e:
      return new Inst_dconst(0);
    case 0x0f:
      return new Inst_dconst(1);
    case 0x10:
      return new Inst_bipush();
    case 0x11:
      return new Inst_sipush();
    case 0x12:  // return new ldc
    case 0x13:  // return new ldc_w
    case 0x14:  // return new ldc2_w
    // Loads
    case 0x15:
      return new Inst_iload(0, false);
    case 0x16:
      return new Inst_lload(0, false);
    case 0x17:
      return new Inst_fload(0, false);
    case 0x18:
      return new Inst_dload(0, false);
    case 0x19:
      return new Inst_aload(0, false);
    case 0x1a:
      return new Inst_iload(0, true);
    case 0x1b:
      return new Inst_iload(1, true);
    case 0x1c:
      return new Inst_iload(2, true);
    case 0x1d:
      return new Inst_iload(3, true);
    case 0x1e:
      return new Inst_lload(0, true);
    case 0x1f:
      return new Inst_lload(1, true);
    case 0x20:
      return new Inst_lload(2, true);
    case 0x21:
      return new Inst_lload(3, true);
    case 0x22:
      return new Inst_fload(0, true);
    case 0x23:
      return new Inst_fload(1, true);
    case 0x24:
      return new Inst_fload(2, true);
    case 0x25:
      return new Inst_fload(3, true);
    case 0x26:
      return new Inst_dload(0, true);
    case 0x27:
      return new Inst_dload(1, true);
    case 0x28:
      return new Inst_dload(2, true);
    case 0x29:
      return new Inst_dload(3, true);
    case 0x2a:
      return new Inst_aload(0, true);
    case 0x2b:
      return new Inst_aload(1, true);
    case 0x2c:
      return new Inst_aload(2, true);
    case 0x2d:
      return new Inst_aload(3, true);
    case 0x2e:
      return new Inst_iaload();
    case 0x2f:  // return new Inst_laload();
    case 0x30:  // return new Inst_faload();
    case 0x31:  // return new Inst_daload();
    case 0x32:  // return new Inst_aaload();
    case 0x33:  // return new Inst_baload();
    case 0x34:  // return new Inst_caload();
    case 0x35:  // return new Inst_saload();
    // Stores
    case 0x36:
      return new Inst_istore(0, false);
    case 0x37:
      return new Inst_lstore(0, false);
    case 0x38:
      return new Inst_fstore(0, false);
    case 0x39:
      return new Inst_dstore(0, false);
    case 0x3a:
      return new Inst_astore(0, false);
    case 0x3b:
      return new Inst_istore(0, true);
    case 0x3c:
      return new Inst_istore(1, true);
    case 0x3d:
      return new Inst_istore(2, true);
    case 0x3e:
      return new Inst_istore(3, true);
    case 0x3f:
      return new Inst_lstore(0, true);
    case 0x40:
      return new Inst_lstore(1, true);
    case 0x41:
      return new Inst_lstore(2, true);
    case 0x42:
      return new Inst_lstore(3, true);
    case 0x43:
      return new Inst_fstore(0, true);
    case 0x44:
      return new Inst_fstore(1, true);
    case 0x45:
      return new Inst_fstore(2, true);
    case 0x46:
      return new Inst_fstore(3, true);
    case 0x47:
      return new Inst_dstore(0, true);
    case 0x48:
      return new Inst_dstore(1, true);
    case 0x49:
      return new Inst_dstore(2, true);
    case 0x4a:
      return new Inst_dstore(3, true);
    case 0x4b:
      return new Inst_astore(0, true);
    case 0x4c:
      return new Inst_astore(1, true);
    case 0x4d:
      return new Inst_astore(2, true);
    case 0x4e:
      return new Inst_astore(3, true);
    case 0x4f:
      return new Inst_iastore();
    case 0x50:  // return new Inst_lastore();
    case 0x51:  // return new Inst_fastore();
    case 0x52:  // return new Inst_dastore();
    case 0x53:  // return new Inst_aastore();
    case 0x54:  // return new Inst_bastore();
    case 0x55:  // return new Inst_castore();
    case 0x56:  // return new Inst_sastore();
    // Stack
    case 0x57:
      return new Inst_pop(false);
    case 0x58:
      return new Inst_pop(true);
    case 0x59:
      return new Inst_dup();
    case 0x5a:
      return new Inst_dup_x1();
    case 0x5b:
      return new Inst_dup_x2();
    case 0x5c:
      return new Inst_dup2();
    case 0x5d:
      return new Inst_dup2_x1();
    case 0x5e:
      return new Inst_dup2_x2();
    case 0x5f:
      return new Inst_swap();
    // Math
    case 0x60:
      return new Inst_iarith(ADD);
    case 0x61:
      return new Inst_larith(ADD);
    case 0x62:
      return new Inst_farith(ADD);
    case 0x63:
      return new Inst_darith(ADD);
    case 0x64:
      return new Inst_iarith(SUB);
    case 0x65:
      return new Inst_larith(SUB);
    case 0x66:
      return new Inst_farith(SUB);
    case 0x67:
      return new Inst_darith(SUB);
    case 0x68:
      return new Inst_iarith(MUL);
    case 0x69:
      return new Inst_larith(MUL);
    case 0x6a:
      return new Inst_farith(MUL);
    case 0x6b:
      return new Inst_darith(MUL);
    case 0x6c:
      return new Inst_iarith(DIV);
    case 0x6d:
      return new Inst_larith(DIV);
    case 0x6e:
      return new Inst_farith(DIV);
    case 0x6f:
      return new Inst_darith(DIV);
    case 0x70:
      return new Inst_iarith(REM);
    case 0x71:
      return new Inst_larith(REM);
    case 0x72:
      return new Inst_farith(REM);
    case 0x73:
      return new Inst_darith(REM);
    case 0x74:
      return new Inst_iarith(NEG);
    case 0x75:
      return new Inst_larith(NEG);
    case 0x76:
      return new Inst_farith(NEG);
    case 0x77:
      return new Inst_darith(NEG);
    case 0x78:
      return new Inst_iarith(SHL);
    case 0x79:
      return new Inst_larith(SHL);
    case 0x7a:
      return new Inst_iarith(SHR);
    case 0x7b:
      return new Inst_larith(SHR);
    case 0x7c:
      return new Inst_iarith(USHR);
    case 0x7d:
      return new Inst_larith(USHR);
    case 0x7e:
      return new Inst_iarith(AND);
    case 0x7f:
      return new Inst_larith(AND);
    case 0x80:
      return new Inst_iarith(OR);
    case 0x81:
      return new Inst_larith(OR);
    case 0x82:
      return new Inst_iarith(XOR);
    case 0x83:
      return new Inst_larith(XOR);
    case 0x84:
      return new Inst_iinc();
    // Conversions
    case 0x85:
      return new Inst_i2l();
    case 0x86:
      return new Inst_i2f();
    case 0x87:
      return new Inst_i2d();
    case 0x88:
      return new Inst_l2i();
    case 0x89:
      return new Inst_l2f();
    case 0x8a:
      return new Inst_l2d();
    case 0x8b:
      return new Inst_f2i();
    case 0x8c:
      return new Inst_f2l();
    case 0x8d:
      return new Inst_f2d();
    case 0x8e:
      return new Inst_d2i();
    case 0x8f:
      return new Inst_d2l();
    case 0x90:
      return new Inst_d2f();
    case 0x91:
      return new Inst_i2b();
    case 0x92:
      return new Inst_i2c();
    case 0x93:
      return new Inst_i2s();
    // Comparisons
    case 0x94:
      return new Inst_lcmp();
    case 0x95:
      return new Inst_fcmp(false);
    case 0x96:
      return new Inst_fcmp(true);
    case 0x97:
      return new Inst_dcmp(false);
    case 0x98:
      return new Inst_dcmp(true);
    case 0x99:
      return new Inst_if(EQ);
    case 0x9a:
      return new Inst_if(NE);
    case 0x9b:
      return new Inst_if(LT);
    case 0x9c:
      return new Inst_if(GE);
    case 0x9d:
      return new Inst_if(GT);
    case 0x9e:
      return new Inst_if(LE);
    case 0x9f:
      return new Inst_if_icmp(EQ);
    case 0xa0:
      return new Inst_if_icmp(NE);
    case 0xa1:
      return new Inst_if_icmp(LT);
    case 0xa2:
      return new Inst_if_icmp(GE);
    case 0xa3:
      return new Inst_if_icmp(GT);
    case 0xa4:
      return new Inst_if_icmp(LE);
    case 0xa5:
      return new Inst_if_acmp(EQ);
    case 0xa6:
      return new Inst_if_acmp(NE);
    // Control
    case 0xa7:
      return new Inst_goto();
    case 0xa8:  // return new Inst_jsr();
    case 0xa9:  // return new ret();
    case 0xaa:
      return new Inst_tableswitch();
    case 0xab:
      return new Inst_lookupswitch();
    case 0xac:  // return new ireturn();
    case 0xad:  // return new lreturn();
    case 0xae:  // return new freturn();
    case 0xaf:  // return new dreturn();
    case 0xb0:  // return new areturn();
    case 0xb1:  // return new return();
      LOG(FATAL) << "Unimplemented instruction";
    // References
    /* 0xb2 ~ 0xc3 */
    case 0xc4:
      return new Inst_wide(getInst());
    case 0xc5:  // return new Inst_multianewarray();
    case 0xc6:
      return new Inst_ifnull();
    case 0xc7:
      return new Inst_ifnonnull();
    case 0xc8:
      return new Inst_goto_w();
    case 0xc9:  // return new Inst_jsr_w();
    // Reserved
    /* 0xca ~ 0xff */
    default:
      LOG(FATAL) << "JVM decode error when decoding opcode: 0x" << std::hex
                 << static_cast<unsigned int>(opcode) << std::dec;
      ;
  }

  // to eliminate warning
  return nullptr;
}

}  // namespace bytecode

}  // namespace coconut
