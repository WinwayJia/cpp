#include <iostream>
#include <functional>

struct Foo {
    void display_greeting() {
        std::cout << "Hello, world.\n";
    }
    void display_number(int i) {
        std::cout << "number: " << i << '\n';
    }
    int data = 7;
};


int main()
{
    std::cout << "Hello world" << std::endl;


    Foo foo;
    auto fn = std::mem_fn(&Foo::display_number);
    fn(foo, 666);
    return 0;
}

