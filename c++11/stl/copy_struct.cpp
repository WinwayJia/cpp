#include <iostream>
#include <map>

using namespace std;

class Empty {
public:
    Empty()  // 缺省构造函数
    {
        cout << __FUNCTION__ << " : " << __LINE__ << endl;
    }
    explicit Empty(const Empty& rhs)  // 拷贝构造函数
    {
        cout << __FUNCTION__ << " : " << __LINE__ << endl;
    }

    ~Empty()  // 析构函数 ---- 是否为虚函数看下文说明
    {
        cout << __FUNCTION__ << " : " << __LINE__ << endl;
    }
    Empty& operator=(const Empty& rhs)  // 赋值运算符
    {
        cout << __FUNCTION__ << " : " << __LINE__ << endl;
    }

    /*    Empty* operator&()             // 取址运算符
        {
        }
        const Empty* operator&() const;
        */
};

int main() {
    Empty e;
    /*    map<int, Empty> m;

        m.insert(pair<int, Empty>(1, e));

        cout << "\n\n\n\n" << endl;
    */
    Empty e1(e);
    Empty e2;
    e2 = e;
    return 0;
}
