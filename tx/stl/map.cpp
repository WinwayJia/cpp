#include <iostream>
#include <unordered_map>

int main() {
    using it = std::unordered_map<std::string, std::string>::iterator;
    using mv = std::move_iterator<it>;

    std::unordered_map<std::string, std::string> temp = {
        { "123", "456" },
    };

    auto iter = temp.find("123");
    std::cout << iter->second << std::endl;
    iter->second.append("456");

    std::unordered_map<std::string, std::string> m;
    m.insert(mv(temp.begin()),mv(temp.end()));

    iter = m.find("123");
    std::cout << iter->second << std::endl;

    return 0;
}

