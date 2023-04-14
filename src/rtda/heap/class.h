/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/heap/class.h
 * \brief java.lang.Class and related classes (Field, Method).
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_HEAP_CLASS_H_
#define SRC_RTDA_HEAP_CLASS_H_

#include "../../classloader/classfile.h"
#include "../../utils/typedef.h"
#include "constant.h"

namespace coconut {

namespace rtda {

// pre-declare Class to avoid cycle reference.
class Class;

/*! \brief Member of a class. Basic class of Field and Method. */
class Member {
 public:
  std::string name;
  std::string descriptor;
  uint16_t accessFlags;
  Class* belong;

  explicit Member(const classloader::MemberInfo& info)
      : name(info.name()),
        descriptor(info.descriptor()),
        accessFlags(info.accessFlags),
        belong(nullptr) {}
};

class Field : Member {
 public:
  unsigned int slotId;

  explicit Field(const classloader::MemberInfo& info)
      : Member(info), slotId(0) {}
};

class Method : Member {
 public:
  unsigned int maxStack;
  unsigned int maxLocals;
  BYTE* code;

  explicit Method(const classloader::MemberInfo& info) : Member(info) {
    classloader::CodeAttr* codeAttr = info.attributes->filtCodeAttr();
    CHECK(codeAttr != nullptr) << "No CodeAttr found";
    maxStack = codeAttr->maxStack;
    maxLocals = codeAttr->maxLocals;
    code = new BYTE[codeAttr->codeLen];
    std::memcpy(code, codeAttr->code, codeAttr->codeLen);
  }

  ~Method() { delete[] code; }
};

/*!
 * \brief java.lang.Class.
 *
 * A more detailed representation of java Class (comparing with ClassFile) in
 * JVM.
 */
class Class {
 public:
  std::string name;

  // fields
  std::vector<Field> fields;

  // methods
  std::vector<Method> methods;

  // super class & interfaces
  Class* superClass;
  std::vector<Class*> interfaces;

  // class file info
  uint16_t accessFlags;
  ConstantPool* cp;

  explicit Class(const classloader::ClassFile& file)
      : name(file.className()), accessFlags(file.accessFlags) {
    cp = new ConstantPool(this, file.cp);
  }
};

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_HEAP_CLASS_H_
