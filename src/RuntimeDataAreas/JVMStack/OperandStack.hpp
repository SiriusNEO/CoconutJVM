/*
 *  JVM Local Variable Table
 */

#pragma once


#include "LocalVariableTable.hpp"

namespace coconut {

using namespace cocotools;

class OperandStack {
    private:
        Slot*         slots;
        unsigned int  top;
        unsigned int  maxStack;

        void up() {
            ++top;
            if (top >= maxStack) {
                panic("OperandStack overflow!");
            }
        }

        void down() {
            --top;
            if (top < 0) {
                panic("OperandStack overflow!");
            }
        }
    
    public:
        OperandStack(unsigned int _maxStack): maxStack(_maxStack), top(0) {
            slots = new Slot[maxStack];
        }

        ~OperandStack() {
            delete[] slots;
        }

        void pushSlot(Slot slot) {
            slots[top] = slot;
            up();
        }

        Slot popSlot() {
            down();
            return slots[top];
        }

        void pushInt(int val) {
            slots[top].bytes = val;
            up();
        }

        int popInt() {
            down();
            return int(slots[top].bytes);
        }

        void pushFloat(float val) {
            slots[top].bytes = *(Slot32*)(&val);
            up();
        }

        float popFloat() {
            down();
            return *(float*)(&slots[top].bytes);
        }

        void pushLong(long long val) {
            // low
            slots[top].bytes = Slot32(val);
            up();
            // high
            slots[top].bytes = Slot32(val >> 32);
            up();
        }

        long long popLong() {
            down();
            long long high = (long long)(slots[top].bytes);
            down();
            long long low = (long long)(slots[top].bytes);
            return (long long)((high << 32) | low);
        }

        void pushDouble(double val) {
            pushLong(*(long long*)(&val));
        }

        double popDouble() {
            long long bits = popLong();
            return *(double*)(&bits);
        }

        void pushRef(Object* ref) {
            slots[top].ref = ref;
            up();
        }

        Object* popRef() {
            down();
            return slots[top].ref;
        }
};


}