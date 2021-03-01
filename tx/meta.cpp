#include <iostream>
#include <type_traits>
#include <functional>

using namespace std;

template <int N>
struct st {
		static const int value = N * st<N-1>::value;
};

template <>
struct st<0> {
		static const int value = 1;
};

template <int N>
constexpr int foo() {
		return N * foo<N-1>();
}

template <>
constexpr int foo<0>() {
		return 1;
}

template<int X>
constexpr int fact() { 
		cout << "he" << endl;
		return X * fact<X - 1>();
}

template <>
constexpr int fact<5>() {
		return 5;
}

constexpr int factorial(int n) { 
		return n <= 1 ? 1 : (n * factorial(n-1));
}

//template <int N> int fact2() { return N * fact<N - 1>(); }
//template <> int fact2<0>() { return 1; }
//

void fun1(int x) {
}

void fun2(int x, int y) {
}

auto main() -> int {
//		cout << st<5>::value << endl;
		cout << foo<5> << endl;
		cout << fact<5> << endl;
		cout << factorial(5) << endl;
//		cout << fact2<5> << endl;
//
    auto f1 = std::bind(fun1, 1);
    auto f2 = std::bind(fun2, 1, 2);
    int x;
//    cout << decltype(f1) << endl;
    std::cout << std::boolalpha << is_same<decltype(f2), decltype(f2)>::value << endl;
}
