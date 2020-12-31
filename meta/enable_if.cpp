#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
typename std::enable_if<(sizeof(T) > 4), T>::type
foo(T value) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << value << std::endl;
}

template <typename T>
// typename std::enable_if<(std::is_pointer<T>::value), T>::type
std::enable_if_t<(std::is_pointer<T>::value), T>
fab(T value) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<typename T, typename = std::enable_if_t<std::is_pointer<T>::value>>
void fab2(T t) {

}


template <int N>
void test() {
    if constexpr (1 == N) {
        std::cout << "N == 1" << std::endl;
        return;
    }
    if constexpr (2 == N) {
        std::cout << "N == 2" << std::endl;
        return;
    }
}

using vector = std::vector<int>;

auto val = std::integral_constant<int, 5>{}; 
using int_type = decltype(val);

int main()
{
    std::cout << "Hello world" << std::endl;
    foo<int64_t>(1000);

    int x = 100;
    fab2(&x);

    const int xx = 2;
    test<xx>();

    int_type x2;
    test<int_type::value>();
    std::cout << x2 << std::endl;
    return 0;
}

