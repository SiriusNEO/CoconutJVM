/*
 *  ConstantPool:
 *     constant pool. Referring to JVM Standard
 */

#pragma once

#include "../utils/typedef.hpp"
#include "../utils/mutf8.hpp"
#include "ByteReader.hpp"
#include <string>
#include <vector>

namespace coconut {

// ConstantPoolTag
const uint8_t CONSTANT_TAG_Utf8                = 1;
const uint8_t CONSTANT_TAG_Integer             = 3;
const uint8_t CONSTANT_TAG_Float               = 4;
const uint8_t CONSTANT_TAG_Long                = 5;
const uint8_t CONSTANT_TAG_Double              = 6;
const uint8_t CONSTANT_TAG_Class               = 7;
const uint8_t CONSTANT_TAG_String              = 8;
const uint8_t CONSTANT_TAG_Fieldref            = 9;
const uint8_t CONSTANT_TAG_Methodref           = 10;
const uint8_t CONSTANT_TAG_InterfaceMethodref  = 11;
const uint8_t CONSTANT_TAG_NameAndType         = 12;
const uint8_t CONSTANT_TAG_MethodHandle        = 15;
const uint8_t CONSTANT_TAG_MethodType          = 16;
const uint8_t CONSTANT_TAG_InvokeDynamic       = 18;


struct ConstantInfo {
    uint8_t  tag;

    ConstantInfo(uint8_t _tag): tag(_tag) {}

    virtual ~ConstantInfo() {}
};

struct ConstantPool;

struct ConstantIntegerInfo: public ConstantInfo {
    // int32
    int  val;

    explicit ConstantIntegerInfo(ByteReader& reader): ConstantInfo(CONSTANT_TAG_Integer) {
        val = int(reader.fetchU4());
    }
};

struct ConstantFloatInfo: public ConstantInfo {
    // float 32
    float  val;
    
    explicit ConstantFloatInfo(ByteReader& reader): ConstantInfo(CONSTANT_TAG_Float) {
        val = float(reader.fetchU4());
    }
};

struct ConstantLongInfo: public ConstantInfo {
    // long 64
    long long  val;

    explicit ConstantLongInfo(ByteReader& reader): ConstantInfo(CONSTANT_TAG_Long) {
        val = (long long)(reader.fetchU8());
    }
};

struct ConstantDoubleInfo: public ConstantInfo {
    // double 64
    double    val;

    explicit ConstantDoubleInfo(ByteReader& reader): ConstantInfo(CONSTANT_TAG_Double) {
        val = double(reader.fetchU8());
    }
};

struct ConstantUtf8Info: public ConstantInfo {
    // utf-8 readable string
    std::string  val;

    explicit ConstantUtf8Info(ByteReader& reader): ConstantInfo(CONSTANT_TAG_Utf8) {
        std::vector<BYTE> bytesBuffer;
        size_t length = size_t(reader.fetchU2());
        reader.fetchBytes(length, bytesBuffer);
        // this cause MemoryLeak: why?
        val = decodeMUTF8FromBytes(bytesBuffer);
        // Log::info("decode: %s", val.c_str());
    }
};

struct ConstantStringInfo: public ConstantInfo {
    ConstantPool*  cp;
    uint16_t       literalIdx;

    ConstantStringInfo(ByteReader& reader, ConstantPool* _cp): cp(_cp), ConstantInfo(CONSTANT_TAG_String) {
        literalIdx = reader.fetchU2();
    }
};

struct ConstantClassInfo: public ConstantInfo {
    ConstantPool*  cp;
    uint16_t       nameIdx;

    ConstantClassInfo(ByteReader& reader, ConstantPool* _cp): cp(_cp), ConstantInfo(CONSTANT_TAG_Class) {
        nameIdx = reader.fetchU2();
    }
};

struct ConstantNameAndTypeInfo: public ConstantInfo {
    ConstantPool*  cp;
    uint16_t       nameIdx;
    uint16_t       descriptorIdx;

    ConstantNameAndTypeInfo(ByteReader& reader, ConstantPool* _cp): cp(_cp), ConstantInfo(CONSTANT_TAG_NameAndType) {
        nameIdx = reader.fetchU2();
        descriptorIdx = reader.fetchU2();
    }
};

struct ConstantRefInfo: public ConstantInfo {
    ConstantPool*  cp;
    uint16_t       classInfoIdx;
    uint16_t       nameAndTypeInfoIdx;

    ConstantRefInfo(ByteReader& reader, ConstantPool* _cp, uint8_t _tag): cp(_cp), ConstantInfo(_tag) {
        classInfoIdx = reader.fetchU2();
        nameAndTypeInfoIdx = reader.fetchU2();
    }
};

struct ConstantPool {
    
    uint16_t infoNum;
    uint16_t cpCount;
    ConstantInfo**  infoList;
    
    ConstantPool(uint16_t _cpCount): infoNum(0), cpCount(_cpCount) {
        infoList = new ConstantInfo* [cpCount];
        for (int i = 0; i < cpCount; ++i) infoList[i] = nullptr;
    }

    ~ConstantPool() {
        if (infoList != nullptr) {
            for (int i = 0; i < cpCount; ++i) 
                if (infoList[i] != nullptr) {
                    delete infoList[i];
                }
            delete [] infoList;
        }
    }

    std::string getLiteral(uint16_t utf8Idx) const {
        ConstantUtf8Info* info = static_cast<ConstantUtf8Info*>(infoList[utf8Idx]);
        return info->val;
    }

    std::string getClassNameStr(uint16_t classIdx) const {
        ConstantClassInfo* info = static_cast<ConstantClassInfo*>(infoList[classIdx]);
        return getLiteral(info->nameIdx);
    }

    std::pair<std::string, std::string> getNameAndTypeStr(uint16_t nameAndTypeIdx) const {
        ConstantNameAndTypeInfo* info = static_cast<ConstantNameAndTypeInfo*>(infoList[nameAndTypeIdx]);
        return std::make_pair(
            getLiteral(info->nameIdx),
            getLiteral(info->descriptorIdx)
        );
    }
};


// from bytes get single ConstantInfo
ConstantInfo* parseSingleConstantInfo(ByteReader& reader, ConstantPool* cp) {
    uint8_t tag = reader.fetchU1();
    switch (tag) {
        case CONSTANT_TAG_Utf8: {
            // Log::info("const utf8");
            return new ConstantUtf8Info(reader);
        }
        case CONSTANT_TAG_Integer: {
            // Log::info("const int");
            return new ConstantIntegerInfo(reader);
        }
        case CONSTANT_TAG_Float: {
            // Log::info("const float");
            return new ConstantFloatInfo(reader);
        }
        case CONSTANT_TAG_Long: {
            // Log::info("const long");
            return new ConstantLongInfo(reader);
        }
        case CONSTANT_TAG_Double: {
            // Log::info("const double");
            return new ConstantDoubleInfo(reader);
        }
        case CONSTANT_TAG_Class: {
            // Log::info("const class");
            return new ConstantClassInfo(reader, cp);
        }
        case CONSTANT_TAG_String: {
            // Log::info("const string");
            return new ConstantStringInfo(reader, cp);
        }
        case CONSTANT_TAG_Fieldref: {
            // Log::info("const fr");
            return new ConstantRefInfo(reader, cp, CONSTANT_TAG_Fieldref);
        }
        case CONSTANT_TAG_Methodref: {
            // Log::info("const mr");
            return new ConstantRefInfo(reader, cp, CONSTANT_TAG_Methodref);
        }
        case CONSTANT_TAG_InterfaceMethodref: {
            // Log::info("const imr");
            return new ConstantRefInfo(reader, cp, CONSTANT_TAG_InterfaceMethodref);
        }
        case CONSTANT_TAG_NameAndType: {
            // Log::info("const name and type");
            return new ConstantNameAndTypeInfo(reader, cp);
        }
        case CONSTANT_TAG_MethodHandle:case CONSTANT_TAG_MethodType:case CONSTANT_TAG_InvokeDynamic: {
            panic("Unimplemented constant pool tag.");
        }
        default: {
            // Log::info("invalid tag: %u", uint32_t(tag));
            panic("parse constant info error");
        }
    }
    // eliminate the warning
    return nullptr;
}

}