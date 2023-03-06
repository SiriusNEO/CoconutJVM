/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/heap/constant.h
 * \brief Runtime Java Constant & ConstantPool.
 * \author SiriusNEO
 */

#include "../../classloader/constant_pool.h"

#ifndef SRC_RTDA_HEAP_CONSTANT_H_
#define SRC_RTDA_HEAP_CONSTANT_H_

namespace coconut {

namespace rtda {

// pre-declare Class to avoid cycle reference.
// The definition is in class.h
class Class;

class Constant {
  // nothing here now
};

class IntConstant : public Constant {
 public:
  const int value;

  explicit IntConstant(int _value) : value(_value) {}
};

class FloatConstant : public Constant {
 public:
  const float value;

  explicit FloatConstant(float _value) : value(_value) {}
};

class LongConstant : public Constant {
 public:
  const long long value;

  explicit LongConstant(long long _value) : value(_value) {}
};

class DoubleConstant : public Constant {
 public:
  const double value;

  explicit DoubleConstant(double _value) : value(_value) {}
};

class StrConstant : public Constant {
 public:
  const std::string value;

  explicit StrConstant(std::string _value) : value(_value) {}
};

class ConstantPool {
 public:
  Class* belong;

  // Not use std::vector because we use the factory. Use ** we can allocate
  // memory dynamically and it's memory-efficient.
  Constant** constants;
};

Constant* constantFactory(const classloader::ConstantInfo* info);

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_HEAP_CONSTANT_H_
