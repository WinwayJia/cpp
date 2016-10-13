#include <tr1/functional>
#include <iostream>
#include <vector>

using namespace std;

class Test
{
 public:
        Test() { ; }
        virtual void foo() = 0;
};

void someFunc(Test& j)
{
    j.foo();
}

class TestChild : public Test
{
    public:
        TestChild() {}
        virtual void foo() override
        {
            cout << __FUNCTION__ << endl;
        }
};

int main()
{
    TestChild tc;
    
//    auto func = std::tr1::bind(someFunc, &tc);
//    func();
    

    vector<int> a;
    cout << sizeof(a) << endl;

#define VALUE_NAME(v) #v
    cout << VALUE_NAME(a) << endl;

//    cout << #a << endl; // error
    return 0;
}
