/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/rtda/thread.h
 * \brief An abstraction for threads in JVM.
 * \author SiriusNEO
 */

#ifndef SRC_RTDA_THREAD_H_
#define SRC_RTDA_THREAD_H_

#include "vmstack/jvm_stack.h"

namespace coconut {

namespace rtda {

/*!
 * \brief Thread abstraction in JVM.
 *
 * Currently the thread is just a simple wrapper of PC (Programming Counter) and
 * a vm stack.
 */
class Thread {
 public:
  /*! \brief The programming counter. */
  int pc;

  /*! \brief The virtual machine stack. */
  JVMStack stack;

  // TODO: change 1024 into an argument in commandline
  Thread() : pc(0), stack(1024) {}
};

}  // namespace rtda

}  // namespace coconut

#endif  // SRC_RTDA_THREAD_H_
