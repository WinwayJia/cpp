#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
void foo (const T& val)
{
    if (std::is_pointer<T>::value) {
        std::cout << "foo() called for a pointer" << std::endl;
    }
    else {
        std::cout << "foo() called for a value" << std::endl;
    }
}

auto main() -> int {
    foo(10);

    auto p = new int(1);
    foo(p);

    return 0;
}
