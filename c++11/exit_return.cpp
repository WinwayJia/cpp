#include <iostream>
#include <stdlib.h>

using namespace std;

class CTest {
    public:
        CTest() {
            cout << "CTest constructor" << endl;
        }
        ~CTest() {
            cout << "CTest destructor" << endl;
        }
};

int main()
{
    CTest t;
    exit(0);
    //return 0;
}
