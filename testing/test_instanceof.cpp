#include <iostream>
#include "../src/utils/instanceof.hpp"

using namespace std;

class Parent {
public:
    virtual ~Parent() {}

};

class Son1: public Parent {
public:
    ~Son1() {}

};

class Son2: public Parent {
public:
    ~Son2() {}
};

using namespace cocotools;

int main() {

    Parent* ptr = new Son1();

    cout << instanceof<Son1>(ptr) << endl;
    cout << instanceof<Son2>(ptr) << endl;

    delete ptr;
}