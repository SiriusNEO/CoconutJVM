/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/slot.h
 * \brief The slot in the table / operand stack.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_VMSTACK_SLOT_H_
#define SRC_RTDA_VMSTACK_SLOT_H_

#include "../../utils/typedef.h"
#include "../heap/object.h"

namespace coconut {

namespace rtda {

/*! \brief A slot in the table is 32bit. */
typedef uint32_t Slot32;

/*!
 * \brief The slot definition in the table. Either to be a data field (slot32
 * bytes) or a ObjectRef.
 *
 * \note In some machine (64bit machine), ref (the pointer) is 64bit. So the
 * union is 64bit. So why long and double still cost 2 slots (in this case, are
 * 128 bits)? It looks like a waste of space. The answer is: obey the standard
 * of JVM.
 */
typedef union {
  Slot32 bytes;
  Object* ref;
} Slot;

};  // namespace rtda

};  // namespace coconut

#endif  // SRC_RTDA_VMSTACK_SLOT_H_
