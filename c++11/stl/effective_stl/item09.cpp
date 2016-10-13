// 永不建立auto_ptr的容器
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <list>
#include <map>
#include <set>
#include <algorithm>

bool rm_func(int x) {
    return x > 3;
}

// vector, deque, string
void test_remove_1() {
    std::vector<int> vec = {3, 5, 1, 4, 7, 6, 2};
    vec.erase(std::remove_if(vec.begin(), vec.end(), rm_func), vec.end());
    for (auto x : vec) {
        std::cout << x << " ";
    } std::cout << std::endl;
}

// list
void test_remove_2() {
    std::list<int> ll = {3, 5, 1, 4, 7, 6, 2};
    ll.remove_if(rm_func);
    for (auto x : ll) {
        std::cout << x << " ";
    } std::cout << std::endl;
}


int main(int argc, char** argv) {
    test_remove_1();
    test_remove_2();

    return 0;
}
