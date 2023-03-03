/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classfile/attributes.h
 * \brief Attributes and AttributeInfo in Java lang.
 * \author SiriusNEO
 */

#ifndef SRC_CLASSFILE_ATTRIBUTES_H_
#define SRC_CLASSFILE_ATTRIBUTES_H_

#include "../utils/misc.h"
#include "constant_pool.h"

namespace coconut {

namespace classfile {

/*! \brief Positions of attributes in the list. */
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

/*! \brief Names of the attributes. */
const std::string ATTRIBUTES_NAMES[] = {
    "Code",         "ConstantValue",   "Deprecated",         "Exceptions",
    "InnerClasses", "LineNumberTable", "LocalVariableTable", "SourceFile",
    "Synthetic",    "Unimplemented"};

/*! \brief The attribute info. Record the position of name instead of name
 * string. */
struct AttributeInfo {
  int namePos;

  AttributeInfo(int _namePos) : namePos(_namePos) {}

  virtual ~AttributeInfo() {}

  std::string getName() const { return ATTRIBUTES_NAMES[namePos]; }
};

/*!
 * \brief Factory of the attribute info. From bytes to get a single
 * AttributeInfo.
 * \param reader The byte reader.
 * \param cp The constant pool. Some info needs it when initializing.
 * \return The constructed attribute info.
 * \note This method allocate new memory for the attribute info. User should
 * delete it manually.
 */
AttributeInfo* attributeInfoFactory(utils::ByteReader& reader,
                                    ConstantPool* cp);

// pre-declare CodeAttr to avoid cycle reference.
struct CodeAttr;

/*! \brief Abstraction of a list of attribute infos. */
struct Attributes {
  uint16_t attributesNum;
  AttributeInfo** list;

  Attributes(utils::ByteReader& reader, ConstantPool* cp) {
    attributesNum = reader.fetchU2();

    list = new AttributeInfo*[attributesNum];

    for (uint16_t i = 0; i < attributesNum; ++i) {
      list[i] = attributeInfoFactory(reader, cp);
    }
  }

  ~Attributes() {
    for (int i = 0; i < attributesNum; ++i) delete list[i];
    delete[] list;
  }

  CodeAttr* filtCodeAttr() {
    for (int i = 0; i < attributesNum; ++i) {
      if (utils:: instanceof <CodeAttr>(list[i])) {
        return (CodeAttr*)list[i];
      }
    }
    return nullptr;
  }
};

/*! \brief The entry of exception table. Used in CodeAttr. */
struct ExceptionTableEntry {
  uint16_t startPc;
  uint16_t endPc;
  uint16_t handlerPc;
  uint16_t catchType;
};

/*!
 * \brief The Code attribute.
 * \note It has some memory fields (code, attributes) to delete.
 */
struct CodeAttr : public AttributeInfo {
  ConstantPool* cp;
  uint16_t maxStack;
  uint16_t maxLocals;
  uint32_t codeLen;
  BYTE* code;
  std::vector<ExceptionTableEntry> exceptionTable;
  Attributes* attributes;

  CodeAttr(utils::ByteReader& reader, ConstantPool* _cp)
      : cp(_cp), AttributeInfo(POS_Code) {
    maxStack = reader.fetchU2();
    maxLocals = reader.fetchU2();

    codeLen = reader.fetchU4();
    code = new BYTE[codeLen];
    reader.fetchBytes(codeLen, code);

    uint16_t exceptionTableLen = reader.fetchU2();
    for (uint16_t i = 0; i < exceptionTableLen; ++i) {
      exceptionTable.push_back(
          (ExceptionTableEntry){reader.fetchU2(), reader.fetchU2(),
                                reader.fetchU2(), reader.fetchU2()});
    }

    attributes = new Attributes(reader, cp);
  }

  ~CodeAttr() {
    delete[] code;
    delete attributes;
  }
};

/*! \brief The ConstantValue attribute. */
struct ConstantValueAttr : public AttributeInfo {
  uint16_t valueIdx;

  ConstantValueAttr(utils::ByteReader& reader)
      : AttributeInfo(POS_ConstantValue) {
    valueIdx = reader.fetchU2();
  }
};

/*! \brief The Deprecated attribute. */
struct DeprecatedAttr : public AttributeInfo {
  DeprecatedAttr() : AttributeInfo(POS_Deprecated) {}
};

/*! \brief The Exceptions attribute. */
struct ExceptionsAttr : public AttributeInfo {
  std::vector<uint16_t> exceptionIndexTable;

  ExceptionsAttr(utils::ByteReader& reader) : AttributeInfo(POS_Exceptions) {
    reader.fetchU2List(exceptionIndexTable);
  }
};

/*! \brief The InnerClass attribute. */
struct InnerClassesAttr : public AttributeInfo {
  // not implement
};

/*! \brief The entry of line number table. Used in LineNumberTableAttr. */
struct LineNumberTableEntry {
  uint16_t startPc;
  uint16_t lineNumber;
};

/*! \brief The LineNumberTable attribute. */
struct LineNumberTableAttr : public AttributeInfo {
  std::vector<LineNumberTableEntry> lineNumberTable;

  LineNumberTableAttr(utils::ByteReader& reader)
      : AttributeInfo(POS_LineNumberTable) {
    uint16_t lineNumberTableLen = reader.fetchU2();

    for (uint16_t i = 0; i < lineNumberTableLen; ++i) {
      lineNumberTable.push_back(
          (LineNumberTableEntry){reader.fetchU2(), reader.fetchU2()});
    }
  }
};

/*! \brief The entry of local variable table. Used in LocalVariableTableAttr. */
struct LocalVariableTableEntry {
  uint16_t startPc;
  uint16_t length;
  uint16_t nameIndex;
  uint16_t descriptorIndex;
  uint16_t index;
};

/*! \brief The LocalVariableTable attribute. */
struct LocalVariableTableAttr : public AttributeInfo {
  std::vector<LocalVariableTableEntry> localVariableTable;

  LocalVariableTableAttr(utils::ByteReader& reader)
      : AttributeInfo(POS_LocalVariableTable) {
    uint16_t localVariableTableLen = reader.fetchU2();

    for (uint16_t i = 0; i < localVariableTableLen; ++i) {
      localVariableTable.push_back(
          (LocalVariableTableEntry){reader.fetchU2(), reader.fetchU2(),
                                    reader.fetchU2(), reader.fetchU2()});
    }
  }
};

/*! \brief The SourceFile attribute. */
struct SourceFileAttr : public AttributeInfo {
  ConstantPool* cp;
  uint16_t fileNameIdx;

  SourceFileAttr(utils::ByteReader& reader, ConstantPool* _cp)
      : cp(_cp), AttributeInfo(POS_SourceFile) {
    fileNameIdx = reader.fetchU2();
  }

  std::string getFileName() const { return cp->getLiteral(fileNameIdx); }
};

/*! \brief The Synthetic attribute. */
struct SyntheticAttr : public AttributeInfo {
  SyntheticAttr() : AttributeInfo(POS_Synthetic) {}
};

/*! \brief Attributes which are unimplemented. Temporarily stored in this
 * structural. */
struct UnimplementedAttr : public AttributeInfo {
  std::string trueAttrName;
  uint32_t attrLen;
  std::vector<BYTE> info;

  UnimplementedAttr(utils::ByteReader& reader, uint32_t _attrLen)
      : attrLen(_attrLen), AttributeInfo(POS_Unimplemented) {
    reader.fetchBytes(attrLen, info);
  }
};

}  // namespace classfile

}  // namespace coconut

#endif  // SRC_CLASSFILE_ATTRIBUTES_H_
