#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>

std::ostream& operator<<(std::ostream& out, std::vector<int> &vec) {
    for (auto x : vec) {
        out << x << " ";
    }
    return out;
}

bool cmp(int x, int y) {
    return x > y;
}

#define DEF_TOTAL (1000 * 1000 * 100)
#define DEF_K (5)

void top_k_sort(std::vector<int> &vec, int k) {
    std::cout << "sort" << std::endl;
    sort(vec.begin(), vec.end(), cmp);
    for (int i=0; i<k; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void top_k_partial_sort(std::vector<int>& vec, int k) {
    std::cout << "partial_sort" << std::endl;
    partial_sort(vec.begin(), vec.begin()+k, vec.end(), cmp);
    for (int i=0; i<k; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void top_k_heap(std::vector<int> &vec, int k) {
    std::cout << "heap_sort" << std::endl;
    std::vector<int> ret;
    for (auto x : vec) {
        if (ret.size() < k) {
            ret.push_back(x);
            if (ret.size() >= k) {
                make_heap(ret.begin(), ret.end(), cmp);
            }
        } else {
            if (x > ret.front()) {
                pop_heap(ret.begin(), ret.end(), cmp);
                ret.back() = x;
                push_heap(ret.begin(), ret.end(), cmp);
            }
        }
    }
    sort(ret.begin(), ret.end(), cmp);
    std::cout << ret << std::endl;
}

void test_stl_heap() {
    std::vector<int> vec = {9, 5, 3, 7, 2, 6, 4, 8, 1, 0};
    std::cout << vec << std::endl;

    make_heap(vec.begin(), vec.end(), cmp);
    std::cout << vec << std::endl;

    pop_heap(vec.begin(), vec.end(), cmp);
    std::cout << vec << std::endl;

    vec.back() = 1;
    push_heap(vec.begin(), vec.end(), cmp);
    std::cout << vec << std::endl;

    sort_heap(vec.begin(), vec.end(), cmp);
    std::cout << vec << std::endl;
}

int main(int argc, char** argv) {
    std::vector<int> vec(DEF_TOTAL);
    for (int i=0; i<DEF_TOTAL; ++i) {
        vec[i] = random();
    } 

    if (argc == 1) {
        top_k_heap(vec, DEF_K);
    } else if (argc == 2) {
        top_k_partial_sort(vec, DEF_K);
    } else {
        top_k_sort(vec, DEF_K);
    }

    return 0;
}
