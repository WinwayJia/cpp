// atomic::operator=/operator T example:
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread, std::this_thread::yield
#include <chrono>    

std::atomic<int> foo(0);

void set_foo(int x) {
	foo = x;
}

void print_foo() {
	while (0 == foo) {             // wait while foo=0
	    std::cout << "foo: " << foo << '\n';
		std::this_thread::yield();
	}
	std::cout << "foo: " << foo << '\n';
}

int main ()
{
	std::thread first(print_foo);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
	std::thread second(set_foo, 10);

	first.join();
	second.join();

	return 0;
}
