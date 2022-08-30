#include <iostream>
#include <cmath>

using namespace std;

int main() {
    cout << 1.0 / 0 << endl;
    cout << -1.0 / 0 << endl;
    cout << 0.0 / 0.0 << endl;
    cout << std::fmod(3, (1.0 / 0.0)) << endl;
    cout << std::fmod(1.0, 0.0) << endl;
}