#include <iostream>

using namespace std;

int main() {
    // logical shr
    // 0011111111111111 = 2^30-1
    cout << ((unsigned int)(-3) >> (unsigned int)2) << endl;
    // 0011111111111110 = 2^30-2
    cout << ((unsigned int)(-7) >> (unsigned int)2) << endl;

    // arithmetic shr
    // 11111...1101  -> 11111...111 = -1
    cout << ((-3) >> 2) << endl;
    // 11111...1001 -> 11111...110 = -2
    cout << ((-7) >> 2) << endl;
}