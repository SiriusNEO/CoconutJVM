/*
 *  Thread
 */

#pragma once


#include "JVMStack/JVMStack.hpp"

namespace coconut {

struct Thread {
    int             pc;
    JVMStack        stack;

    Thread(): pc(0), stack(1024) {}
};

}