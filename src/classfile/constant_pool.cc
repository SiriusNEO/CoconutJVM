/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classfile/constant_pool.cc
 * \brief Implementation of constant_pool.h
 * \author SiriusNEO
 */

#include "constant_pool.h"

namespace coconut {

namespace classfile {

std::string ConstantPool::getLiteral(uint16_t utf8Idx) const {
  ConstantUtf8Info* info = static_cast<ConstantUtf8Info*>(infoList[utf8Idx]);
  return info->val;
}

std::string ConstantPool::getClassNameStr(uint16_t classIdx) const {
  ConstantClassInfo* info = static_cast<ConstantClassInfo*>(infoList[classIdx]);
  return getLiteral(info->nameIdx);
}

std::pair<std::string, std::string> ConstantPool::getNameAndTypeStr(
    uint16_t nameAndTypeIdx) const {
  ConstantNameAndTypeInfo* info =
      static_cast<ConstantNameAndTypeInfo*>(infoList[nameAndTypeIdx]);
  return std::make_pair(getLiteral(info->nameIdx),
                        getLiteral(info->descriptorIdx));
}

ConstantInfo* constantInfoFactory(utils::ByteReader& reader, ConstantPool* cp) {
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
    case CONSTANT_TAG_MethodHandle:
    case CONSTANT_TAG_MethodType:
    case CONSTANT_TAG_InvokeDynamic: {
      LOG(FATAL) << "Unimplemented constant pool tag.";
    }
    default: {
      LOG(FATAL) << "Parse constant info error. Invalid tag: " << uint32_t(tag);
    }
  }
  // eliminate the warning
  return nullptr;
}

}  // namespace classfile
}  // namespace coconut
