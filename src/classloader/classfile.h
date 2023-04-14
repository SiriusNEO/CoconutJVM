/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/classfile.h
 * \brief ClassFile: contains all information about one single Java class.
 * \author SiriusNEO
 */

#ifndef SRC_CLASSLOADER_CLASSFILE_H_
#define SRC_CLASSLOADER_CLASSFILE_H_

#include "attributes.h"

namespace coconut {

namespace classloader {

/*! \brief Java class file magic number: cafe babe. */
const int JAVA_CLASS_MAGIC = 0xCAFEBABE;

/*! \brief Info of members in Java. */
class MemberInfo {
 public:
  ConstantPool* cp;
  uint16_t accessFlags;
  uint16_t nameIdx;
  uint16_t descriptorIdx;

  Attributes* attributes;

  MemberInfo(utils::ByteReader& reader, ConstantPool* _cp) : cp(_cp) {
    accessFlags = reader.fetchU2();
    nameIdx = reader.fetchU2();
    descriptorIdx = reader.fetchU2();

    attributes = new Attributes(reader, cp);
  }

  MemberInfo(MemberInfo&& other)
      : cp(other.cp),
        accessFlags(other.accessFlags),
        nameIdx(other.nameIdx),
        descriptorIdx(other.descriptorIdx) {
    attributes = other.attributes;
    other.attributes = nullptr;
  }

  std::string name() const { return cp->getLiteral(nameIdx); }

  std::string descriptor() const { return cp->getLiteral(descriptorIdx); }

  ~MemberInfo() {
    if (attributes != nullptr) delete attributes;
  }
};

/*!
 * \brief ClassFile in Java: the information of a total class file.
 *
 * It contains the total information of a java class.
 * We implement the "classfile loader" in the constructor of ClassFile, that is,
 * converting bytes to a ClassFile.
 * With file loader (file_loader.h), we get a complete classfile loader of our
 * JVM.
 *
 * A complete Java class has the following information:
 *  magic                 uint32
 *  minorVersion          uint16
 *  majorVersion          uint16
 *  constantPool          ConstantPool
 *  accessFlags           uint16
 *  thisClass             uint16
 *  superClass            uint16
 *  interfaces            uint16[]
 *  fields                FieldsInfo[]
 *  methods               FieldsInfo[]
 *  attributes            AttributeInfo[]
 */
class ClassFile {
 public:
  // uint32_t  magic        (no need to store)
  uint16_t minorVersion;
  uint16_t majorVersion;

  ConstantPool* cp;

  uint16_t accessFlags;

  uint16_t thisClass;
  uint16_t superClass;

  std::vector<uint16_t> interfaces;
  std::vector<MemberInfo> fields;
  std::vector<MemberInfo> methods;

  Attributes* attributes;

  /*!
   * \brief Default constructor. Convert bytes into a ClassFile.
   * \param reader The byte reader.
   */
  ClassFile(utils::ByteReader& reader);

  /*! \brief The default destructor. */
  ~ClassFile() {
    if (cp != nullptr) {
      delete cp;
    }
    if (attributes != nullptr) {
      delete attributes;
    }
  }

  /*!
   * \brief Get the class name.
   * \return The class name.
   */
  std::string className() const { return cp->getClassNameStr(thisClass); }

  /*!
   * \brief Get the super class name.
   * \return The super class name.
   */
  std::string superClassName() const {
    if (superClass == 0) {
      // no superClass (May be java.lang.Object). Return empty string.
      return "";
    }
    return cp->getClassNameStr(superClass);
  }

  /*!
   * \brief Display the class file.
   */
  void display() const;
};

}  // namespace classloader

}  // namespace coconut

#endif  // SRC_CLASSLOADER_CLASSFILE_H_
