#include "../src/RuntimeDataAreas/JVMStack/JVMStack.hpp"
#include "../src/utils/log.hpp"

using namespace coconut;

int main() {
    JVMStack vmStack(10);
    
    vmStack.push(100, 100);

    Log::info("local variable test");
    vmStack.topFrame->localVariableTable->setInt(0, 123);
    vmStack.topFrame->localVariableTable->setFloat(1, 3.14);
    vmStack.topFrame->localVariableTable->setInt(2, -99);
    vmStack.topFrame->localVariableTable->setLong(3, 21474836470);
    vmStack.topFrame->localVariableTable->setDouble(5, 2.71828182845);
    Object obj;
    vmStack.topFrame->localVariableTable->setRef(7, &obj);
    Log::info("%d", vmStack.topFrame->localVariableTable->getInt(2));
    Log::info("%lld", vmStack.topFrame->localVariableTable->getLong(3));
    Log::info("%f", vmStack.topFrame->localVariableTable->getFloat(1));
    Log::info("%.11lf", vmStack.topFrame->localVariableTable->getDouble(5));
    Log::info("%d %d", &obj, vmStack.topFrame->localVariableTable->getRef(7));


    Log::info("operand stack test");
    vmStack.topFrame->operandStack->pushInt(100);
    vmStack.topFrame->operandStack->pushInt(-100);
    vmStack.topFrame->operandStack->pushLong(2997924580);
    vmStack.topFrame->operandStack->pushLong(-2997924580);
    vmStack.topFrame->operandStack->pushFloat(3.1415926);
    vmStack.topFrame->operandStack->pushDouble(2.71828182845);
    vmStack.topFrame->operandStack->pushRef(nullptr);

    Log::info("%d", vmStack.topFrame->operandStack->popAndGetRef());
    Log::info("%.11lf", vmStack.topFrame->operandStack->popAndGetDouble());
    Log::info("%f", vmStack.topFrame->operandStack->popAndGetFloat());
    Log::info("%lld", vmStack.topFrame->operandStack->popAndGetLong());
    Log::info("%lld", vmStack.topFrame->operandStack->popAndGetLong());
    Log::info("%d", vmStack.topFrame->operandStack->popAndGetInt());
    Log::info("%d", vmStack.topFrame->operandStack->popAndGetInt());

    vmStack.pop();

    return 0;
}