/*
 *  Java Virtual Machine Stack
 */

#pragma once


#include "OperandStack.hpp"


namespace coconut {

// prevent cross-include
struct Thread;

class JVMStack;

struct StackFrame {
    LocalVariableTable*   localVariableTable;
    OperandStack*         operandStack;
    Thread*               thread;
    int                   nextPc;


    StackFrame(unsigned int maxLocals, unsigned int maxStack, StackFrame* _lowFrame): lowFrame(_lowFrame) {
        localVariableTable = new LocalVariableTable(maxLocals);
        operandStack = new OperandStack(maxStack);
    }

    ~StackFrame() {
        if (localVariableTable != nullptr) {
            delete localVariableTable;
        }
        if (operandStack != nullptr) {
            delete operandStack;
        }
    }

    friend JVMStack;

private:     
    // linked list. To prevent from allocating all memory at first.
    // (allocate when using)
    StackFrame*  lowFrame; 
};

class JVMStack {
    private:
        unsigned int     capacity;

    public:
        unsigned int     size;
        StackFrame*      topFrame;

        JVMStack(unsigned int _capacity): 
        capacity(_capacity), size(0), topFrame(nullptr) {}

        ~JVMStack() {
            clear();
        }

        bool isEmpty() const {
            return topFrame == nullptr;
        }

        void clear() {
            while (!isEmpty()) {
                pop();
            }
        }

        // construct it automatically
        void push(unsigned int maxLocals, unsigned int maxStack) {
            if (size >= capacity) {
                panic("java.lang.StackOverflowError");
            }
            if (isEmpty()) {
                topFrame = new StackFrame(maxLocals, maxStack, nullptr);
            }
            else {
                topFrame = new StackFrame(maxLocals, maxStack, topFrame);
            }
            ++size;
        }

        // destruct it automatically. not return
        void pop() {
            if (isEmpty()) {
                panic("JVMStack is empty! can not pop.");
            }
            StackFrame* popped = topFrame;
            topFrame = topFrame->lowFrame;
            delete popped;
        }
};

}