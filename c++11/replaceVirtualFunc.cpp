#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <tr1/memory>
#include <tr1/functional>

using namespace std;

class Foo
{
    public:
        void methodA() {
            cout << __FUNCTION__ << endl;
        }
        void methodInt(int a) {
            cout << __FUNCTION__ << " a = " << a <<endl;
        }
        void methodInt(int a, int b) {
            cout << __FUNCTION__ << " a = " << a << " b = " << b <<endl;
        }
};

class Bar
{
    public:
        void methodB() {
            cout << __FUNCTION__ << endl;
        }
};

int main(int argc, char** argv)
{
    boost::function<void()> f1; // 无参数，无返回值

    Foo foo;
    f1 = boost::bind(&Foo::methodA, &foo);
    f1(); // 调用 foo.methodA();
    Bar bar;
    f1 = boost::bind(&Bar::methodB, &bar);
    f1(); // 调用 bar.methodB();

    f1 = boost::bind(&Foo::methodInt, &foo, 42);
    f1(); // 调用 foo.methodInt(42);

    boost::function<void(int)> f2; // int 参数，无返回值
    f2 = boost::bind(&Foo::methodInt, &foo, _1);
    f2(53); // 调用 foo.methodInt(53);

    f2 = boost::bind(&Foo::methodInt, &foo, 20, _1);
    f2(40);

    boost::function<void(int, int)> f3;
    f3 = boost::bind(&Foo::methodInt, &foo, _1, _2);
    f3(40, 80);

    tr1::function<void(int)> f4;
    f4 = tr1::bind(&Foo::methodInt, &foo);
    f4(10);

    return 0;
}
