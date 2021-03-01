#include <iostream>
#include <string>

struct Demo {
    int  x = 10;
};

std::string get() {
    std::string str = std::string("Hello") + "World";
    return str;
}

int main() {
    Demo d;
    std::cout << d.x << std::endl;

    std::string x1 = get();
    std::string x2 = std::move(get());

    std::cout << x1 << std::endl << x2 << std::endl;
}
