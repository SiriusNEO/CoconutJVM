/*!
 * \file src/rtda/heap/constant.cc
 * \brief Implementation of constant.h
 * \author SiriusNEO
 */

#include "constant.h"

#include "ref.h"

namespace coconut {

namespace rtda {

Constant* constantFactory(const classloader::ConstantInfo* info,
                          ConstantPool* cp) {
  switch (info->tag) {
    case classloader::CONSTANT_TAG_Integer:
      return new IntConstant(
          dynamic_cast<const classloader::ConstantIntegerInfo*>(info)->val);
    case classloader::CONSTANT_TAG_Float:
      return new FloatConstant(
          dynamic_cast<const classloader::ConstantFloatInfo*>(info)->val);
    case classloader::CONSTANT_TAG_Long:
      return new LongConstant(
          dynamic_cast<const classloader::ConstantLongInfo*>(info)->val);
    case classloader::CONSTANT_TAG_Double:
      return new DoubleConstant(
          dynamic_cast<const classloader::ConstantDoubleInfo*>(info)->val);
    case classloader::CONSTANT_TAG_Fieldref:
      return new FieldRef(
          *dynamic_cast<const classloader::ConstantRefInfo*>(info), cp);
    case classloader::CONSTANT_TAG_Methodref:
      return new MethodRef(
          *dynamic_cast<const classloader::ConstantRefInfo*>(info), cp);
    case classloader::CONSTANT_TAG_InterfaceMethodref:
      return new InterfaceMethodRef(
          *dynamic_cast<const classloader::ConstantRefInfo*>(info), cp);
    default:
      LOG(FATAL) << "Unknown ConstantInfo type.";
  }
  return nullptr;  // elimnaite warning: -Wreturn-type
}

}  // namespace rtda

}  // namespace coconut
