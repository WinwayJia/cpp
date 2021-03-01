#include <iostream>
#include <vector>
#include <utility>

std::vector<int> get_vec() {
    std::vector<int> vec = {1, 2, 3};
    return vec;
}

int main()
{
    std::cout << "Hello world" << std::endl;

    auto vec = get_vec();

    auto vec2 = std::move(vec);
    for (auto & x : vec2) {
        std::cout << x << std::endl;
    }
    return 0;
}

