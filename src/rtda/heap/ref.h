/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/heap/ref.h
 * \brief Classes of runtime symbolic reference in constant pool.
 * \author SiriusNEO
 */

#include "class.h"
#include "constant.h"

#ifndef SRC_RTDA_HEAP_REF_H_
#define SRC_RTDA_HEAP_REF_H_

namespace coconut {

namespace rtda {

/*!
 * \brief Symbolic reference of a java Class.
 *
 * Symbolic reference uses a symbol (string) to index into the constant pool and
 * find the true object in it.
 */
class SymbolicRef : public Constant {
 protected:
  std::string symbol_;

 public:
  ConstantPool* cp;

  SymbolicRef(std::string symbol, ConstantPool* _cp)
      : cp(_cp), symbol_(symbol) {}
};

class ClassRef : public SymbolicRef {
 public:
  Class* refClass;

  ClassRef(const classloader::ConstantClassInfo& info, ConstantPool* _cp)
      : SymbolicRef(info.name(), _cp), refClass(nullptr) {}

  std::string className() const { return symbol_; }
};

class MemberRef : public SymbolicRef {
 public:
  Class* belongClass;
  std::string memberName;
  std::string descriptor;

  MemberRef(const classloader::ConstantRefInfo& info, ConstantPool* _cp)
      : SymbolicRef(info.className(), _cp), belongClass(nullptr) {
    auto nameAndDescriptor = info.nameAndDescriptor();
    memberName = nameAndDescriptor.first;
    descriptor = nameAndDescriptor.second;
  }
};

class FieldRef : public MemberRef {
 public:
  Field* field;

  FieldRef(const classloader::ConstantRefInfo& info, ConstantPool* _cp)
      : MemberRef(info, _cp), field(nullptr) {}
};

class MethodRef : public MemberRef {
 public:
  Method* method;

  MethodRef(const classloader::ConstantRefInfo& info, ConstantPool* _cp)
      : MemberRef(info, _cp), method(nullptr) {}
};

class InterfaceMethodRef : public MemberRef {
 public:
  Method* interfaceMethod;

  InterfaceMethodRef(const classloader::ConstantRefInfo& info,
                     ConstantPool* _cp)
      : MemberRef(info, _cp), interfaceMethod(nullptr) {}
};

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_HEAP_REF_H_
