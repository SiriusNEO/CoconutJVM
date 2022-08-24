/*
 *  ClassInfo:
 *     contains all information about one single .class file.
 */

#pragma once

#include "ByteReader.hpp"
#include "ConstantPool.hpp"
#include "../utils/panic.hpp"
#include <vector>

namespace coconut {

// cafe babe
const int JAVA_CLASS_MAGIC = 0xCAFEBABE;

struct AttributeInfo {
    uint16_t  attributeNameIndex;
    uint32_t  attributeLength;
    uint8_t*   info;
};

struct FieldInfo {
    ConstantPool*  constantPool;
    uint16_t  accessFlags;
    uint16_t  nameIndex;
    uint16_t  descriptorIndex;
    std::vector<AttributeInfo> attributes;
};

typedef FieldInfo MethodInfo;

struct ClassInfo {
    // uint32_t  magic        (not store)
    uint16_t  minorVersion;
    uint16_t  majorVersion;
    
    ConstantPool constantPool;

    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;

    std::vector<uint16_t> interfaces;
    std::vector<FieldInfo> fields;
    std::vector<MethodInfo> methods;
    std::vector<AttributeInfo> attributes;

    // bytes -> java class info (parse java info from bytes)
    ClassInfo(ByteReader reader) {
        // 1. check magic number
        uint32_t magic = reader.fetchU4();
        if (magic != JAVA_CLASS_MAGIC) {
            panic("java.lang.ClassFormatError: magic!");
        }

        // 2. check version
        minorVersion = reader.fetchU2();
        majorVersion = reader.fetchU2();
        if (majorVersion < 45 || majorVersion > 52) {
            panic("java.lang.UnsupportedClassVersionError!");
        }
        // from 46, minor version is deprecated
        if (majorVersion >= 46 && minorVersion != 0) {
            panic("java.lang.UnsupportedClassVersionError!");
        }

        // access flag
        accessFlags = reader.fetchU2();

        thisClass = reader.fetchU2();
        superClass = reader.fetchU2();


    }
};

}