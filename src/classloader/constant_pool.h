/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/constant_pool.h
 * \brief ConstantPool (Referring to JVM Standard).
 * \author SiriusNEO
 */

#ifndef SRC_CLASSLOADER_CONSTANT_POOL_H_
#define SRC_CLASSLOADER_CONSTANT_POOL_H_

#include "../utils/byte_reader.h"
#include "../utils/mutf8.h"
#include "../utils/typedef.h"

namespace coconut {

namespace classloader {

/*! \brief Constant Pool tag. */
const uint8_t CONSTANT_TAG_Utf8 = 1;
const uint8_t CONSTANT_TAG_Integer = 3;
const uint8_t CONSTANT_TAG_Float = 4;
const uint8_t CONSTANT_TAG_Long = 5;
const uint8_t CONSTANT_TAG_Double = 6;
const uint8_t CONSTANT_TAG_Class = 7;
const uint8_t CONSTANT_TAG_String = 8;
const uint8_t CONSTANT_TAG_Fieldref = 9;
const uint8_t CONSTANT_TAG_Methodref = 10;
const uint8_t CONSTANT_TAG_InterfaceMethodref = 11;
const uint8_t CONSTANT_TAG_NameAndType = 12;
const uint8_t CONSTANT_TAG_MethodHandle = 15;
const uint8_t CONSTANT_TAG_MethodType = 16;
const uint8_t CONSTANT_TAG_InvokeDynamic = 18;

/*! \brief Base class of all constant info. */
class ConstantInfo {
 public:
  uint8_t tag;

  ConstantInfo(uint8_t _tag) : tag(_tag) {}

  virtual ~ConstantInfo() {}
};

/*!
 * \brief Runtime constant pool in JVM.
 *
 * A constant pool contains the constants that are needed to run the code of a
 * specific class. Basically, it's a runtime data structure similar to the
 * symbol table. It is a per-class or per-interface runtime representation in a
 * Java class file.
 */
class ConstantPool {
 private:
  /*! \brief Max number of info allocated for constant pool. */
  uint16_t cpCount_;

 public:
  /*! \brief Numer of constant info. */
  uint16_t infoNum;

  /*! \brief The list of constant info in the pool. Not use std::vector because
   * we use the factory. Use ** we can allocate memory dynamically and it's
   * memory-efficient. */
  ConstantInfo** infoList;

  /*!
   * \brief Default constructor.
   * \param cpCount Max number of info allocated for constant pool.
   */
  ConstantPool(uint16_t cpCount) : infoNum(0), cpCount_(cpCount) {
    infoList = new ConstantInfo*[cpCount_];
    for (int i = 0; i < cpCount_; ++i) infoList[i] = nullptr;
  }

  /*! \brief Default destructor. */
  ~ConstantPool() {
    if (infoList != nullptr) {
      for (int i = 0; i < cpCount_; ++i)
        if (infoList[i] != nullptr) {
          delete infoList[i];
        }
      delete[] infoList;
    }
  }

  /*!
   * \brief Get a literal string from the pool.
   * \param utf8Idx The index of the utf8.
   * \return The utf8 string.
   */
  std::string getLiteral(uint16_t utf8Idx) const;

  /*!
   * \brief Get the name of a specific class in the pool.
   * \param classIdx The index of the class.
   * \return The name of the class
   */
  std::string getClassNameStr(uint16_t classIdx) const;

  /*!
   * \brief Get the name-and-type string pair in the pool.
   * \param nameAndTypeIdx The index of name-and-type.
   * \return The name-and-type string pair.
   */
  std::pair<std::string, std::string> getNameAndTypeStr(
      uint16_t nameAndTypeIdx) const;
};

/*! \brief Constant info for an Int. */
class ConstantIntegerInfo : public ConstantInfo {
 public:
  // int32
  int val;

  explicit ConstantIntegerInfo(utils::ByteReader& reader)
      : ConstantInfo(CONSTANT_TAG_Integer) {
    val = int(reader.fetchU4());
  }
};

/*! \brief Constant info for a Float. */
class ConstantFloatInfo : public ConstantInfo {
 public:
  // float 32
  float val;

  explicit ConstantFloatInfo(utils::ByteReader& reader)
      : ConstantInfo(CONSTANT_TAG_Float) {
    val = float(reader.fetchU4());
  }
};

/*! \brief Constant info for a Long. */
class ConstantLongInfo : public ConstantInfo {
 public:
  // long 64
  long long val;

  explicit ConstantLongInfo(utils::ByteReader& reader)
      : ConstantInfo(CONSTANT_TAG_Long) {
    val = (long long)(reader.fetchU8());
  }
};

/*! \brief Constant info for a Double. */
class ConstantDoubleInfo : public ConstantInfo {
 public:
  // double 64
  double val;

  explicit ConstantDoubleInfo(utils::ByteReader& reader)
      : ConstantInfo(CONSTANT_TAG_Double) {
    val = double(reader.fetchU8());
  }
};

/*! \brief Constant info for Utf8 literal. */
class ConstantUtf8Info : public ConstantInfo {
 public:
  // utf-8 readable string
  std::string val;

  explicit ConstantUtf8Info(utils::ByteReader& reader)
      : ConstantInfo(CONSTANT_TAG_Utf8) {
    std::vector<BYTE> bytesBuffer;
    size_t length = size_t(reader.fetchU2());
    reader.fetchBytes(length, bytesBuffer);
    // FIXME: this cause MemoryLeak: why?
    // Not sure whether it has been fixed.
    val = utils::decodeMUTF8FromBytes(bytesBuffer);
  }
};

/*! \brief Constant info for a String. */
class ConstantStringInfo : public ConstantInfo {
 public:
  ConstantPool* cp;
  uint16_t literalIdx;

  ConstantStringInfo(utils::ByteReader& reader, ConstantPool* _cp)
      : cp(_cp), ConstantInfo(CONSTANT_TAG_String) {
    literalIdx = reader.fetchU2();
  }
};

/*! \brief Constant info for class. */
class ConstantClassInfo : public ConstantInfo {
 public:
  ConstantPool* cp;
  uint16_t nameIdx;

  ConstantClassInfo(utils::ByteReader& reader, ConstantPool* _cp)
      : cp(_cp), ConstantInfo(CONSTANT_TAG_Class) {
    nameIdx = reader.fetchU2();
  }

  std::string name() const { return cp->getLiteral(nameIdx); }
};

/*! \brief Constant info for name-and-type. */
class ConstantNameAndTypeInfo : public ConstantInfo {
 public:
  ConstantPool* cp;
  uint16_t nameIdx;
  uint16_t descriptorIdx;

  ConstantNameAndTypeInfo(utils::ByteReader& reader, ConstantPool* _cp)
      : cp(_cp), ConstantInfo(CONSTANT_TAG_NameAndType) {
    nameIdx = reader.fetchU2();
    descriptorIdx = reader.fetchU2();
  }
};

/*! \brief Constant info for Reference. */
class ConstantRefInfo : public ConstantInfo {
 public:
  ConstantPool* cp;
  uint16_t classInfoIdx;
  uint16_t nameAndTypeInfoIdx;

  ConstantRefInfo(utils::ByteReader& reader, ConstantPool* _cp, uint8_t _tag)
      : cp(_cp), ConstantInfo(_tag) {
    classInfoIdx = reader.fetchU2();
    nameAndTypeInfoIdx = reader.fetchU2();
  }

  std::string className() const { return cp->getClassNameStr(classInfoIdx); }

  std::pair<std::string, std::string> nameAndDescriptor() const {
    return cp->getNameAndTypeStr(nameAndTypeInfoIdx);
  }
};

/*!
 * \brief Factory of the constant info. From bytes to get a single ConstantInfo.
 * \param reader The byte reader.
 * \param cp The constant pool. Some info needs it when initializing.
 * \return The constructed constant info.
 * \note This method allocate new memory for the constant info. User should
 * delete it manually.
 */
ConstantInfo* constantInfoFactory(utils::ByteReader& reader, ConstantPool* cp);

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_CONSTANT_POOL_H_
