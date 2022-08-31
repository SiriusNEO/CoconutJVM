/*
 *  command line panic
 */

#pragma once

#include <cstdio>
#include <cstdlib>
#include <stdarg.h>
#include <cassert>

namespace cocotools {

static void panic(const char* format, ...) {
    printf("coconut panic: ");

    va_list v_args;
    va_start(v_args, format);
    vprintf(format, v_args);
    printf("\n");
    va_end(v_args);

    exit(1);
}

}