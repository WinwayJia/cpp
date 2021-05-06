#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T>& vec) {
    std::for_each(vec.begin(), vec.end(),
                  [&out](const T& v) { out << v << " "; });

    return out;
}

int main(int argc, char const* argv[]) {
    std::vector<int> vec(10);
    auto dump_vec = [&vec]() {
        std::for_each(vec.begin(), vec.end(),
                      [](int x) { std::cout << x << " "; });
        std::cout << std::endl;
    };

    std::fill(vec.begin(), vec.end(), -1);
    dump_vec();

    std::generate(vec.begin(), vec.end(), []() -> int {
        static int x = 0;
        return x++;
    });
    dump_vec();

    std::vector<std::string> strings;
    std::transform(
        vec.begin(), vec.end(), std::back_insert_iterator(strings),
        [](int x) -> std::string { return "number: " + std::to_string(x); });
    std::cout << strings << std::endl;

    if (std::any_of(vec.begin(), vec.end(),
                    [](int x) -> bool { return x % 2 == 0; })) {
        std::cout << "has even number" << std::endl;
    }

    if (std::all_of(vec.begin(), vec.end(), [](int x)->bool{return x > -1;})) {
        std::cout << "all number greater than -1" << std::endl;
    }

    std::cout << std::count_if(vec.begin(), vec.end(), [](int x)->bool{return x>5;}) << std::endl;
    std::cout << std::count(vec.begin(), vec.end(), 1) << std::endl;

    return 0;
}
