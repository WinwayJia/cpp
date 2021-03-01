#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, float> weight_logic_map;

    for (int i=0; i<100; i++) {
        if (weight_logic_map[std::to_string(i)]) {
            std::cout << "true" << std::endl;
            continue;
        } 
        std::cout << "false" << std::endl;
    }
}
