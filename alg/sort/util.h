#ifndef __SORT_UTIL_H__
#define __SORT_UTIL_H__
#include <iostream>
#include <vector>

inline void swap(std::vector<int>& vec, int i, int j) {
    auto tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
}

inline std::ostream& operator<<(std::ostream& o, const std::vector<int>& vec) {
    for (auto i : vec) {
        o << i << " ";
    }

    return o;
}

void bubble_sort(std::vector<int>& vec);
void quick_sort(std::vector<int>& vec);

int binary_search(const std::vector<int>& vec, int target);

#endif // __SORT_UTIL_H__