// Test rtda/vmstack

#include <gtest/gtest.h>

#include "../src/rtda/vmstack/jvm_stack.h"

// test local_variable_table

TEST(RTDA_VMSTACK, LocalVariableTable) {
  coconut::rtda::JVMStack vmStack(10);

  vmStack.push(100, 100);

  vmStack.topFrame->localVariableTable->setInt(0, 123);
  vmStack.topFrame->localVariableTable->setFloat(1, 3.14);
  vmStack.topFrame->localVariableTable->setInt(2, -99);
  vmStack.topFrame->localVariableTable->setLong(3, 21474836470);
  vmStack.topFrame->localVariableTable->setDouble(5, 2.71828182845);
  coconut::rtda::Object obj;
  vmStack.topFrame->localVariableTable->setRef(7, &obj);

  EXPECT_EQ(-99, vmStack.topFrame->localVariableTable->getInt(2));
  EXPECT_EQ((long long)21474836470,
            vmStack.topFrame->localVariableTable->getLong(3));
  EXPECT_EQ((float)3.14, vmStack.topFrame->localVariableTable->getFloat(1));
  EXPECT_EQ((double)2.71828182845,
            vmStack.topFrame->localVariableTable->getDouble(5));
  EXPECT_EQ(&obj, vmStack.topFrame->localVariableTable->getRef(7));
}

// test operand_stack

TEST(RTDA_VMSTACK, OperandStack) {
  coconut::rtda::JVMStack vmStack(10);

  vmStack.push(100, 100);

  vmStack.topFrame->operandStack->pushInt(100);
  vmStack.topFrame->operandStack->pushInt(-100);
  vmStack.topFrame->operandStack->pushLong(2997924580);
  vmStack.topFrame->operandStack->pushLong(-2997924580);
  vmStack.topFrame->operandStack->pushFloat(3.1415926);
  vmStack.topFrame->operandStack->pushDouble(2.71828182845);
  vmStack.topFrame->operandStack->pushRef(nullptr);

  EXPECT_EQ(nullptr, vmStack.topFrame->operandStack->popRef());
  EXPECT_EQ((double)2.71828182845, vmStack.topFrame->operandStack->popDouble());
  EXPECT_EQ((float)3.1415926, vmStack.topFrame->operandStack->popFloat());
  EXPECT_EQ((long long)-2997924580, vmStack.topFrame->operandStack->popLong());
  EXPECT_EQ((long long)2997924580, vmStack.topFrame->operandStack->popLong());
  EXPECT_EQ(-100, vmStack.topFrame->operandStack->popInt());
  EXPECT_EQ(100, vmStack.topFrame->operandStack->popInt());
}
