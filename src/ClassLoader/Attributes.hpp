/*
 *  AttributeInfo:
 *     many attributes
 */

#pragma once

#include "ConstantPool.hpp"

namespace coconut {

const int POS_Code = 0;
const int POS_ConstantValue = 1;
const int POS_Deprecated = 2;
const int POS_Exceptions = 3;
const int POS_InnerClasses = 4;
const int POS_LineNumberTable = 5;
const int POS_LocalVariableTable = 6;
const int POS_SourceFile = 7;
const int POS_Synthetic = 8;
const int POS_Unimplemented = 9;

const std::string ATTRIBUTES_NAMES[] = {
    "Code",
    "ConstantValue",
    "Deprecated",
    "Exceptions",
    "InnerClasses",
    "LineNumberTable",
    "LocalVariableTable",
    "SourceFile",
    "Synthetic",
    "Unimplemented"
};

struct AttributeInfo {
    int namePos;

    AttributeInfo(int _namePos) : namePos(_namePos) {}

    virtual ~AttributeInfo() {}

    std::string getName() const { return ATTRIBUTES_NAMES[namePos]; }
};

AttributeInfo* attributeInfoFactory(ByteReader& reader, ConstantPool* cp);

struct Attributes {
    uint16_t attributesNum;
    AttributeInfo** list;

    Attributes(ByteReader& reader, ConstantPool* cp) {
        attributesNum = reader.fetchU2();

        list = new AttributeInfo*[attributesNum];

        for (uint16_t i = 0; i < attributesNum; ++i) {
            list[i] = attributeInfoFactory(reader, cp);
        }
    }

    ~Attributes() {
        for (int i = 0; i < attributesNum; ++i)
            delete list[i];
        delete [] list;
    }
};

struct ExceptionTableEntry {
    uint16_t  startPc;
    uint16_t  endPc;
    uint16_t  handlerPc;
    uint16_t  catchType;
};

struct CodeAttr: public AttributeInfo {
    ConstantPool*  cp;
    uint16_t       maxStack;
    uint16_t       maxLocals;
    std::vector<BYTE>  code;
    std::vector<ExceptionTableEntry> exceptionTable;
    Attributes*    attributes;

    CodeAttr(ByteReader& reader, ConstantPool* _cp): cp(_cp), AttributeInfo(POS_Code) {
        maxStack = reader.fetchU2();
        maxLocals = reader.fetchU2();

        uint32_t codeLen = reader.fetchU4();
        reader.fetchBytes(codeLen, code);

        uint16_t exceptionTableLen = reader.fetchU2();
        for (uint16_t i = 0; i < exceptionTableLen; ++i) {
            exceptionTable.push_back((ExceptionTableEntry){
                reader.fetchU2(),
                reader.fetchU2(),
                reader.fetchU2(),
                reader.fetchU2()
            });
        }

        attributes = new Attributes(reader, cp);
    }

    ~CodeAttr() {
        delete attributes;
    }
};

struct ConstantValueAttr: public AttributeInfo {
    uint16_t  valueIdx;

    ConstantValueAttr(ByteReader& reader): AttributeInfo(POS_ConstantValue) {
        valueIdx = reader.fetchU2();
    }
};

struct DeprecatedAttr: public AttributeInfo {
    DeprecatedAttr(): AttributeInfo(POS_Deprecated) {}
};

struct ExceptionsAttr: public AttributeInfo {
    std::vector<uint16_t>  exceptionIndexTable;

    ExceptionsAttr(ByteReader& reader): AttributeInfo(POS_Exceptions) {
        reader.fetchU2List(exceptionIndexTable);
    }
};

struct InnerClassesAttr: public AttributeInfo {
    // not implement
};

struct LineNumberTableEntry {
    uint16_t  startPc;
    uint16_t  lineNumber;
};

struct LineNumberTableAttr: public AttributeInfo {
    std::vector<LineNumberTableEntry> lineNumberTable;

    LineNumberTableAttr(ByteReader& reader): AttributeInfo(POS_LineNumberTable) {
        uint16_t lineNumberTableLen = reader.fetchU2();
        
        for (uint16_t i = 0; i < lineNumberTableLen; ++i) {
            lineNumberTable.push_back((LineNumberTableEntry) {
                reader.fetchU2(),
                reader.fetchU2()
            });
        }
    }
};

struct LocalVariableTableEntry {
    uint16_t   startPc;     
    uint16_t   length;         
    uint16_t   nameIndex;       
    uint16_t   descriptorIndex;
    uint16_t   index;           
};

struct LocalVariableTableAttr: public AttributeInfo {
    std::vector<LocalVariableTableEntry> localVariableTable;

    LocalVariableTableAttr(ByteReader& reader): AttributeInfo(POS_LocalVariableTable) {
        uint16_t localVariableTableLen = reader.fetchU2();
        
        for (uint16_t i = 0; i < localVariableTableLen; ++i) {
            localVariableTable.push_back((LocalVariableTableEntry) {
                reader.fetchU2(),
                reader.fetchU2(),
                reader.fetchU2(),
                reader.fetchU2()
            });
        }
    }
};

struct SourceFileAttr: public AttributeInfo {
    ConstantPool*  cp;
    uint16_t       fileNameIdx;

    SourceFileAttr(ByteReader& reader, ConstantPool* _cp): cp(_cp), AttributeInfo(POS_SourceFile) {
        fileNameIdx = reader.fetchU2();
    }

    std::string getFileName() const {
        return cp->getLiteral(fileNameIdx);
    }
};

struct SyntheticAttr: public AttributeInfo {
    SyntheticAttr(): AttributeInfo(POS_Synthetic) {}
};

struct UnimplementedAttr: public AttributeInfo {
    std::string  trueAttrName;
    uint32_t          attrLen;
    std::vector<BYTE> info;

    UnimplementedAttr(ByteReader& reader, uint32_t _attrLen): attrLen(_attrLen), AttributeInfo(POS_Unimplemented) {
        reader.fetchBytes(attrLen, info);
    }
};

AttributeInfo* attributeInfoFactory(ByteReader& reader, ConstantPool* cp) {
    uint16_t attrNameIdx = reader.fetchU2();
    uint32_t attrLen = reader.fetchU4();
    std::string attrName = cp->getLiteral(attrNameIdx);
    
    int namePos = 9;
    for (int i = 0; i < 9; ++i) {
        if (attrName == ATTRIBUTES_NAMES[i]) {
            namePos = i;
            break;
        }
    }

    switch (namePos) {
        case POS_Code: {
            // Log::info("code attr");
            return new CodeAttr(reader, cp);
        }
        case POS_ConstantValue: {
            // Log::info("cv attr");
            return new ConstantValueAttr(reader);
        }
        case POS_Deprecated: {
            // Log::info("dep attr");
            return new DeprecatedAttr();
        }
        case POS_Exceptions: {
            // Log::info("exp attr");
            return new ExceptionsAttr(reader);
        }
        case POS_LineNumberTable: {
            // Log::info("lnt attr");
            return new LineNumberTableAttr(reader);
        }
        case POS_LocalVariableTable: {
            // Log::info("lvt attr");
            return new LocalVariableTableAttr(reader);
        }
        case POS_SourceFile: {
            // Log::info("sf attr");
            return new SourceFileAttr(reader, cp);
        }
        case POS_Synthetic: {
            // Log::info("syn attr");
            return new SyntheticAttr();
        }
        default: {
            return new UnimplementedAttr(reader, attrLen);
        }
    }
}

}