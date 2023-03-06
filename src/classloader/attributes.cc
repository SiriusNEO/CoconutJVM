/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/classloader/attributes.cc
 * \brief Implementation of attributes.h
 * \author SiriusNEO
 */

#include "attributes.h"

namespace coconut {

namespace classloader {

AttributeInfo* attributeInfoFactory(utils::ByteReader& reader,
                                    ConstantPool* cp) {
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
      // LOG(INFO) << "code attr";
      return new CodeAttr(reader, cp);
    }
    case POS_ConstantValue: {
      // LOG(INFO) << "cv attr";
      return new ConstantValueAttr(reader);
    }
    case POS_Deprecated: {
      // LOG(INFO) << "dep attr";
      return new DeprecatedAttr();
    }
    case POS_Exceptions: {
      // LOG(INFO) << "exp attr";
      return new ExceptionsAttr(reader);
    }
    case POS_LineNumberTable: {
      // LOG(INFO) << "lnt attr";
      return new LineNumberTableAttr(reader);
    }
    case POS_LocalVariableTable: {
      // LOG(INFO) << "lvt attr";
      return new LocalVariableTableAttr(reader);
    }
    case POS_SourceFile: {
      // LOG(INFO) << "sf attr";
      return new SourceFileAttr(reader, cp);
    }
    case POS_Synthetic: {
      // LOG(INFO) << "syn attr";
      return new SyntheticAttr();
    }
    default: {
      return new UnimplementedAttr(reader, attrLen);
    }
  }
}

}  // namespace classloader

}  // namespace coconut
