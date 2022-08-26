/*
 *  JVM Local Variable Table
 */

#pragma once


#include "../../utils/typedef.hpp"
#include "../../utils/panic.hpp"
#include "../Heap/Object.hpp"

namespace coconut {

// <=32bit: 1 slot
// 64bit (long, double): 2 slot
// ref: 1 slot
// In 64bit machine, ref(the pointer) is 64bit.
// So the union is 64bit, which seems stupid: why not store long and double directly?
// The answer is: obey the standard of JVM.

typedef uint32_t Slot32;

typedef union {
    Slot32     bytes;
    Object*    ref;
} Slot;

using namespace cocotools;

class LocalVariableTable {
    private:
        Slot*         slots;
        unsigned int  maxLocals;

        void checkOverflow(unsigned int index) {
            if (index >= maxLocals) {
                panic("LocalVariableTable overflow!");
            }
        }
    
    public:
        LocalVariableTable(unsigned int _maxLocals): maxLocals(_maxLocals) {
            slots = new Slot[maxLocals];
        }

        ~LocalVariableTable() {
            delete[] slots;
        }

        void setInt(unsigned int index, int32_t val) {
            checkOverflow(index);
            slots[index].bytes = val;
        }

        int32_t getInt(unsigned int index) {
            checkOverflow(index);
            return int32_t(slots[index].bytes);
        }

        void setFloat(unsigned int index, float val) {
            checkOverflow(index);
            // turn float into Slot32 (bitwise)
            // if you use (Slot)(val), round up will happen
            slots[index].bytes = *(Slot32*)(&val);
        }

        float getFloat(unsigned int index) {
            checkOverflow(index);
            return *(float*)(&slots[index].bytes);
        }

        void setLong(unsigned int index, long long val) {
            checkOverflow(index+1);
            // low
            slots[index].bytes = Slot32(val);
            // high
            slots[index+1].bytes = Slot32(val >> 32);
        }

        long long getLong(unsigned int index) {
            checkOverflow(index+1);
            return (((long long)(slots[index+1].bytes) << 32) | (long long)(slots[index].bytes));
        }

        void setDouble(unsigned int index, double val) {
            setLong(index, *(long long*)(&val));
        }

        double getDouble(unsigned int index) {
            long long bits = getLong(index);
            return *(double*)(&bits);
        }

        void setRef(unsigned int index, Object* ref) {
            checkOverflow(index);
            slots[index].ref = ref;
        }

        Object* getRef(unsigned int index) {
            checkOverflow(index);
            return slots[index].ref;
        }
};


}