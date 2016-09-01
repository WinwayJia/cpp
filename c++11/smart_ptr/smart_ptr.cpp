#include <iostream>
#include <memory>

using namespace std;

class A {
    public:
    A () : m_x(10) {
        cout << " constructor() " << endl;
    }
    ~A() {
        cout << " destructor() " << endl;
    }

    void Print() {
        cout << " Print() " << m_x << endl;
    }
    private:
    int         m_x;
    A(const A& a) {
        cout << " copy constructor() " << endl;
    }
//    public:
    const A& operator =(const A& a) {
        return a;
    }
};

// 做参数调用拷贝构造函数 ---------------
int test(A &a)
{
}
//----------------------------------------

// auto_ptr
void sink(auto_ptr<A>& a) {
    cout << " Enter sink" << endl;
}

int test_auto_ptr() {
    auto_ptr<A> a(new A());
    a->Print();
    sink(a);
    a->Print();
}

int main(int argc, char** argv) {
    //test_auto_ptr();

    A a;
    A aa;
    aa = a;
    //test(a);
    return 0;
}
