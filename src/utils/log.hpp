/*
 *  The log
 */

#pragma once

#include <cstdio>
#include <stdarg.h>

namespace cocotools {

    namespace Log {
        
        static void info(const char* format, ...) {
            printf("[INFO] ");
            va_list v_args;
            va_start(v_args, format);
            vprintf(format, v_args);
            printf("\n");
            va_end(v_args);
        }

        static void err(const char* format, ...) {
            printf("[ERR] ");
            va_list v_args;
            va_start(v_args, format);
            vprintf(format, v_args);
            printf("\n");
            va_end(v_args);
        }

        static void warn(const char* format, ...) {
            printf("[WARN] ");
            va_list v_args;
            va_start(v_args, format);
            vprintf(format, v_args);
            printf("\n");
            va_end(v_args);
        }
    }

}