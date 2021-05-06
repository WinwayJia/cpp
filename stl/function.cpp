#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

int mem_fn() {
    std::vector<std::string> v = {"once", "upon", "a", "time"};
    std::transform(v.begin(), v.end(),
                   std::ostream_iterator<std::size_t>(std::cout, " "),
                   //    std::mem_fun_ref(&std::string::size));
                   std::mem_fn(&std::string::size));
    return 0;
}

void run(const std::function<void()> &fn) { fn(); }
void run2(std::function<void()> &&fn) { fn(); }
void run3(std::function<void()> &&fn) { fn(); }

class Demo {
  public:
    void sayHello() {
        std::cout << "from " << __PRETTY_FUNCTION__ << std::endl;
    }

    static void staticFunc() {
        std::cout << "from " << __PRETTY_FUNCTION__ << std::endl;
    }
};

void hi() {}

int main(int argc, char const *argv[]) {
    auto x = []() { std::cout << "in lambda" << std::endl; };
    auto y = [](const std::string &str) {
        std::cout << "in lambda"
                  << ", " << str << std::endl;
    };

    run(x);
    run(std::bind(y, "hello from parameter"));

    Demo d;
    run(std::bind(&Demo::sayHello, &d));
    run(std::bind(std::mem_fn(&Demo::sayHello), &d));

    //    auto t = std::mem_fn(&hi);
    auto t1 = &Demo::sayHello;
    auto t2 = std::mem_fn(&Demo::sayHello);
    std::cout << "& and std::mem_fn(&) is same? " << std::boolalpha
              << std::is_same<decltype(t1), decltype(t2)>::value << std::endl;

    run(std::bind(&Demo::staticFunc));  // ok
    run(std::bind(Demo::staticFunc));   // ok, without &

    std::cout << std::boolalpha
              << std::is_same<decltype(run), decltype(run2)>::value << " "
              << std::is_same<decltype(run3), decltype(run2)>::value << " "
              << std::is_same<decltype(hi), decltype(&hi)>::value << std::endl;

    mem_fn();
    return 0;
}
