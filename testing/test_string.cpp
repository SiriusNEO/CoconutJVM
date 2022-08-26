#include <iostream>

int main() {
    unsigned char* bytes = new unsigned char[233];
    std::string str(bytes, bytes + 666);
    delete[] bytes;
    return 0;
}