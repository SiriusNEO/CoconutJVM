/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/heap/object.h
 * \brief java.lang.Object representation.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_HEAP_OBJECT_H_
#define SRC_RTDA_HEAP_OBJECT_H_

#include "../slot.h"
#include "class.h"

namespace coconut {

namespace rtda {

/*!
 * \brief java.lang.Object.
 */
class Object {
 public:
  Class* objClass;
  SlotList fields;

  explicit Object(unsigned int capacity)
      : objClass(nullptr), fields(capacity) {}
};

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_HEAP_OBJECT_H_
