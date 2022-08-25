#include <iostream>

const std::string ATTRIBUTES_NAMES[] = {
    "Code",
    "ConstantValue",
    "Deprecated",
    "Exceptions",
    "InnerClasses",
    "LineNumberTable",
    "LocalVariableTable",
    "SourceFile",
    "Synthetic"
};

using namespace std;

int main() {
    cout << ATTRIBUTES_NAMES[8] << endl;
}