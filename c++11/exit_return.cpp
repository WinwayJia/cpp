#include <stdlib.h>

#include <iostream>

using namespace std;

// https://stackoverflow.com/questions/3463551/what-is-the-difference-between-exit-and-return

class CTest {
public:
    CTest() { cout << "CTest constructor" << endl; }
    ~CTest() { cout << "CTest destructor" << endl; }
};

int main() {
    CTest t;
    // exit(0);
    return 0;
}
