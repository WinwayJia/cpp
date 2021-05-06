// c++中对函数模板默认参数的支持
#include <iostream>
#include <string>
using namespace std;

template <class T = int>  // c++98 can't with default value
T Max(const T& a, const T& b) {
    return a > b ? a : b;
}

template <class T = string>  // both c++98 and c++11 ok
class Test {};

int main() {
    cout << Max(10, 20) << endl;

    return 0;
}
