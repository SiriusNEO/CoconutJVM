/*
 *  ConstantPoolInfo:
 *     constant pool. Referring to JVM Standard
 */

#pragma once

#include "../utils/typedef.hpp"
#include "ByteReader.hpp"
#include <string>
#include <vector>

namespace coconut {

// ConstantPoolTag
const int CONSTANT_TAG_Utf8                = 1;
const int CONSTANT_TAG_Integer             = 3;
const int CONSTANT_TAG_Float               = 4;
const int CONSTANT_TAG_Long                = 5;
const int CONSTANT_TAG_Double              = 6;
const int CONSTANT_TAG_Class               = 7;
const int CONSTANT_TAG_String              = 8;
const int CONSTANT_TAG_Fieldref            = 9;
const int CONSTANT_TAG_Methodref           = 10;
const int CONSTANT_TAG_InterfaceMethodref  = 11;
const int CONSTANT_TAG_NameAndType         = 12;
const int CONSTANT_TAG_MethodHandle        = 15;
const int CONSTANT_TAG_MethodType          = 16;
const int CONSTANT_TAG_InvokeDynamic       = 18;


struct ConstantPoolInfo {};

struct ConstantPool {
    std::vector<ConstantPoolInfo> infoList;
};

struct ConstantIntegerInfo: public ConstantPoolInfo {
    uint32_t  val;
};

struct ConstantFloatInfo: public ConstantPoolInfo {
    uint32_t  val;
};

struct ConstantLongInfo: public ConstantPoolInfo {
    uint64_t  val;
};

struct ConstantDoubleInfo: public ConstantPoolInfo {
    double    val;
};

struct ConstantUtf8Info: public ConstantPoolInfo {
    std::string  val;
};

struct ConstantStringInfo: public ConstantPoolInfo {
    ConstantPool*  constantPool;
    uint16_t       strLiteralIndex;
};

struct ConstantClassInfo: public ConstantPoolInfo {
    ConstantPool*  constantPool;
    uint16_t       nameLiteralIndex;
};

struct ConstantNameAndTypeInfo: public ConstantPoolInfo {
    ConstantPool*  constantPool;
    uint16_t       nameLiteralIndex;
    uint16_t        descriptorLiteralIndex;
};

struct ConstantRefInfo: public ConstantPoolInfo {
    ConstantPool*  constantPool;
    uint16_t       classInfoIndex;
    uint16_t       nameAndTypeInfoIndex;
};

void parseSingleConstantInfoFromBytes(ByteReader reader) {
    uint8_t tag = reader.fetchU1();
    switch (tag) {
        case CONSTANT_TAG_Utf8: {
            break;
        }
        case CONSTANT_TAG_Integer: {
            break;
        }
        case CONSTANT_TAG_Float: {
            break;
        }
        case CONSTANT_TAG_Long: {
            break;
        }
        case CONSTANT_TAG_Double: {
            break;
        }
        case CONSTANT_TAG_Class: {
            break;
        }
        case CONSTANT_TAG_String: {
            break;
        }
        case CONSTANT_TAG_Fieldref: {
            break;
        }
        case CONSTANT_TAG_Methodref: {
            break;
        }
        case CONSTANT_TAG_InterfaceMethodref: {
            break;
        }
        case CONSTANT_TAG_NameAndType: {
            break;
        }
        case CONSTANT_TAG_MethodHandle:case CONSTANT_TAG_MethodType:case CONSTANT_TAG_InvokeDynamic: {
            panic("Unimplemented constant pool tag.");
            break;
        }
    }
}

}