#include <iostream>
#include <vector>

void printHex(void* ptr, int size) {
    for (int i=0; i<size; i++) {
        printf("%02x ", *(uint8_t*)ptr);
    }
    puts("\n");
}

std::vector<int> retVec() {
    std::vector<int> vec = { 1, 2, 3 };
    vec.push_back(4);

    printHex(&vec, 8);
    return vec;
}

auto main() -> int {
    {
        std::vector<int> vec;
        vec.reserve(16);
        std::cout << "size: " << vec.size() << std::endl;
    }

    {
        std::vector<int> vec;
        vec.resize(16);
        std::cout << "size: " << vec.size() << std::endl;
    }

    {
        std::vector<int> vec;
        vec.push_back(10);
    }

    auto vec = retVec();
    printHex(&vec, 8);

    std::vector<int> vv;
    vv = retVec();
    printHex(&vv, 8);

    return 0;
}
