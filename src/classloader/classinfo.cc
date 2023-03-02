/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/classinfo.cc
 * \brief Implementation of classinfo.h
 * \author SiriusNEO
 */

#include "classinfo.h"

namespace coconut {

namespace classloader {

ClassInfo::ClassInfo(utils::ByteReader& reader)
    : cp(nullptr), attributes(nullptr) {
  /*
   *  1. check magic number
   */
  uint32_t magic = reader.fetchU4();
  CHECK(magic == JAVA_CLASS_MAGIC) << "java.lang.ClassFormatError: magic!";

  /*
   *  2. check version
   */
  minorVersion = reader.fetchU2();
  majorVersion = reader.fetchU2();
  CHECK(majorVersion >= 45 && majorVersion <= 52)
      << "java.lang.UnsupportedClassVersionError!";
  // from 46, minor version is deprecated
  CHECK(majorVersion < 46 || minorVersion != 0)
      << "java.lang.UnsupportedClassVersionError!";

  /*
   *  3. constant pool
   */
  uint16_t cpCount = reader.fetchU2();
  cp = new ConstantPool(cpCount);
  // notice: cpCnt - 1
  for (uint16_t i = 1; i < cpCount; ++i) {
    // 1-based
    cp->infoList[i] = constantInfoFactory(reader, cp);
    cp->infoNum++;
    if (cp->infoList[i]->tag == CONSTANT_TAG_Long ||
        cp->infoList[i]->tag == CONSTANT_TAG_Double) {
      // notice: long and double take two positions
      ++i;
    }
  }
  LOG(INFO) << "constant pool finish";

  /*
   *  4. access flags & classes & interfaces
   */
  accessFlags = reader.fetchU2();
  thisClass = reader.fetchU2();
  superClass = reader.fetchU2();
  reader.fetchU2List(interfaces);
  LOG(INFO) << "access flags & classes & interfaces finish";

  /*
   *  5. fields & methods & attributes
   */
  uint16_t fieldCount = reader.fetchU2();
  for (uint16_t i = 0; i < fieldCount; ++i) {
    fields.emplace_back(FieldInfo(reader, cp));
  }
  LOG(INFO) << "fields finish";

  uint16_t methodCount = reader.fetchU2();
  for (uint16_t i = 0; i < methodCount; ++i) {
    methods.emplace_back(FieldInfo(reader, cp));
  }
  LOG(INFO) << "methods finish";

  attributes = new Attributes(reader, cp);
}

void ClassInfo::display() const {
  std::ostringstream s;
  s << "--- [ClassInfo] ---\n"
    << "Version: " << uint32_t(majorVersion) << "." << uint32_t(minorVersion)
    << "\n"
    << "Constant Pool: total " << uint32_t(cp->infoNum) << "\n"
    << "Access Flags: " << uint32_t(accessFlags) << "\n"
    << "This Class: " << className().c_str() << "\n"
    << "Super Class: " << superClassName().c_str() << "\n";

  s << "Interfaces: ";
  for (auto interfaceIdx : interfaces) {
    s << cp->getClassNameStr(interfaceIdx).c_str() << " ";
  }
  s << "\n";
  s << "Fields: total " << uint32_t(fields.size()) << "\n";
  for (const auto& field : fields) {
    s << "\t" << field.fieldName().c_str() << "\n";
  }
  s << "Methods: total " << uint32_t(methods.size()) << "\n";
  for (const auto& method : methods) {
    s << "\t" << method.fieldName().c_str() << "\n";
  }
  // display
  LOG(INFO) << s.str();
}

}  // namespace classloader

}  // namespace coconut
