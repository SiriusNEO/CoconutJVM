/*
 *  Thread
 */

#pragma once


#include "JVMStack/JVMStack.hpp"

namespace coconut {

struct Thread {
    int             pc;
    JVMStack        stack;

    // TODO: 1024 -> an argument in commandline
    Thread(): pc(0), stack(1024) {}
};

}