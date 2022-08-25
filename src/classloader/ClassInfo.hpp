/*
 *  ClassInfo:
 *     contains all information about one single .class file.
 */

#pragma once

#include "ByteReader.hpp"
#include "ConstantPool.hpp"
#include "Attributes.hpp"
#include "../utils/panic.hpp"
#include <vector>

namespace coconut {

// cafe babe
const int JAVA_CLASS_MAGIC = 0xCAFEBABE;


struct FieldInfo {
    ConstantPool*  cp;
    uint16_t  accessFlags;
    uint16_t  nameIdx;
    uint16_t  descriptorIdx;

    Attributes* attributes;

    FieldInfo(ByteReader& reader, ConstantPool* _cp): cp(_cp) {
        accessFlags = reader.fetchU2();
        nameIdx = reader.fetchU2();
        descriptorIdx = reader.fetchU2();
        
        attributes = new Attributes(reader, cp);
    }

    std::string fieldName() const {
        return cp->getLiteral(nameIdx);
    } 

    ~FieldInfo() {
        // delete attributes;
    }
};


typedef FieldInfo MethodInfo;

class ClassInfo {
public:
    // uint32_t  magic        (not store)
    uint16_t  minorVersion;
    uint16_t  majorVersion;
    
    ConstantPool* cp;

    uint16_t accessFlags;
    
    uint16_t thisClass;
    uint16_t superClass;

    std::vector<uint16_t> interfaces;
    std::vector<FieldInfo> fields;
    std::vector<MethodInfo> methods;
    
    Attributes* attributes;

    // bytes -> java class info (parse java info from bytes)
    ClassInfo(ByteReader& reader) {
        /* 
         *  1. check magic number
         */
        uint32_t magic = reader.fetchU4();
        if (magic != JAVA_CLASS_MAGIC) {
            panic("java.lang.ClassFormatError: magic!");
        }

        /* 
         *  2. check version
         */
        minorVersion = reader.fetchU2();
        majorVersion = reader.fetchU2();
        if (majorVersion < 45 || majorVersion > 52) {
            panic("java.lang.UnsupportedClassVersionError!");
        }
        // from 46, minor version is deprecated
        if (majorVersion >= 46 && minorVersion != 0) {
            panic("java.lang.UnsupportedClassVersionError!");
        }
        
        /* 
         *  3. constant pool
         */
        uint16_t cpCount = reader.fetchU2();
        cp = new ConstantPool(cpCount);
        // notice: cpCnt - 1
        for (uint16_t i = 1; i < cpCount; ++i) {
            // 1-based
            cp->infoList[i] = parseSingleConstantInfo(reader, cp);
            if (cp->infoList[i]->tag == CONSTANT_TAG_Long || 
                cp->infoList[i]->tag == CONSTANT_TAG_Double) {
                    // notice: long and double take two positions
                    ++i;
                }
        }
        Log::info("constant pool finish");

        /* 
         *  4. access flags & classes & interfaces
         */
        accessFlags = reader.fetchU2();
        thisClass = reader.fetchU2();
        superClass = reader.fetchU2();
        reader.fetchU2List(interfaces);
        Log::info("access flags & classes & interfaces finish");

        /* 
         *  5. fields & methods & attributes
         */
        uint16_t fieldCount = reader.fetchU2();
        for (uint16_t i = 0; i < fieldCount; ++i) {
            fields.emplace_back(FieldInfo(reader, cp));
        }
        Log::info("fields finish");

        uint16_t methodCount = reader.fetchU2();
        for (uint16_t i = 0; i < methodCount; ++i) {
            methods.emplace_back(FieldInfo(reader, cp));
        }
        Log::info("methods finish");

        attributes = new Attributes(reader, cp);
    }

    ~ClassInfo() {
        delete cp;
        // delete attributes;
    }

    std::string className() const {
        return cp->getClassNameStr(thisClass);
    }

    std::string superClassName() const {
        if (superClass == 0) {
            // no superClass. java.lang.Object
            return "";
        }
        return cp->getClassNameStr(superClass);
    }

    void display() const {
        printf("--- [ClassInfo] ---\n");
        printf("Version: %u.%u\n", uint32_t(majorVersion), uint32_t(minorVersion));
        printf("Constant Pool: total %u\n", uint32_t(cp->infoNum));
        printf("Access Flags: %u\n", uint32_t(accessFlags));
        printf("This Class: %s\n", className().c_str());
        printf("Super Class: %s\n", superClassName().c_str());
        printf("Interfaces: ");
        for (auto interfaceIdx: interfaces) {
            printf("%s ", cp->getClassNameStr(interfaceIdx).c_str());
        }
        printf("\n");
        printf("Fields: total %u\n", uint32_t(fields.size()));
        for (const auto& field : fields) {
            printf("\t%s\n", field.fieldName().c_str());
        }
        printf("Methods: total %u\n", uint32_t(methods.size()));
        for (const auto& method : methods) {
            printf("\t%s\n", method.fieldName().c_str());
        }
    }
};

}