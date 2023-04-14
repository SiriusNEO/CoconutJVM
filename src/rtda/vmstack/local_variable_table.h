/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/vmstack/local_variable_table.h
 * \brief JVM Local Variable Table.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_VMSTACK_LOCAL_VARIABLE_TABLE_H_
#define SRC_RTDA_VMSTACK_LOCAL_VARIABLE_TABLE_H_

#include "../slot.h"

namespace coconut {

namespace rtda {

/*!
 * \brief Local Variable Table of JVM.
 *
 * It is in a frame of the JVM Stack. It stores values of local variables in
 * current scope. A slot is 32bit in JVM convention so long/double take two
 * slots.
 */
typedef SlotList LocalVariableTable;

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_VMSTACK_LOCAL_VARIABLE_TABLE_H_
