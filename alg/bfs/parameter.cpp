#include "../sort/util.h"
#include "util.h"

int a(int x) {
    std::cout << "x=" << x << std::endl;
    return x;
}

int b(int x, int y) { return x - y; }

int main() {
    // https://stackoverflow.com/questions/2934904/order-of-evaluation-in-c-function-parameters
    // The order of evaluation of arguments is unspecified.
    // Better code can be generated in the absence of restrictions on expression evaluation order.
    std::cout << a(10) - a(5) << std::endl; // a(10) firstly called

    std::cout << b(a(10), a(5)) << std::endl; // a(5) firstly called

    std::cout << b(a(10) + a(5), 20) << std::endl; // a(10) firstly called

    std::cout << "++++++" << std::endl;
    std::cout << a(10) << "\n" << a(6) << std::endl; // a(10) firstly called

    return 0;
}