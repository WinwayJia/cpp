#include <iostream>
#include <stdio.h>
using namespace std;

class CTest 
{
    public: 
    CTest() {
        cout << " Constructor " << endl;
    }
    virtual ~CTest() {
        cout << " Destructor " << endl;
    }
    virtual void Show() const {
        cout << " Show " << endl;
    }
    virtual void Print() const {
        cout << " Print " << endl;
    }
};

int main()
{
    CTest t;
    typedef void (*fn)();

    fn f = (fn)(((long long int*)(*(long long int*)&t))[2]);
    f();
    printf("%p\n", (long long int*)f);

    f = (fn)(((long long int*)(*(long long int*)&t))[3]);
    f();
    printf("%p\n", (long long int*)f);

    f = (fn)(((long long int*)(*(long long int*)&t))[0]);
    f();
    printf("%p\n", (long long int*)f);

    
    t.Show();
    return 0;
}
