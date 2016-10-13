#include <vector>
#include <iostream>
#include <algorithm>

template <class T>
void myFunc(const T &t) {
    std::cout << t << std::endl;
}

// bool in vector
void test_bool_vector() {
    std::vector<bool> vec = {false, true, false};
    for_each(vec.begin(), vec.end(), myFunc<bool>); 

    bool *p = &vec[0];
    std::vector<int> vecInt = {10, 30, 20};
    for_each(vec.begin(), vec.end(), myFunc<int>); 
    int *pInt = &vecInt[0];
    *pInt = 40;
    for_each(vecInt.begin(), vecInt.end(), myFunc<int>); 
}

void test_reserve() {
    std::vector<int>  vec;
    //vec[0] = 100; core dump
    std::cout << "size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;
    vec.reserve(10);
    vec[0] = 100;
    std::cout << "size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;
}

int main(int argc, char** argv) {
    test_reserve();
    test_bool_vector();
}
