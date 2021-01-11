#include "util.h"
#include <vector>

int partion(std::vector<int>& vec, int b, int e) {
    int j = b;
    for (int i = b; i < e; i++) {
        if (vec[i] <= vec[b]) {
            swap(vec, i, j);
            j++;
        }
    }

    swap(vec, j - 1, b);

    return j - 1;
}

void do_sort(std::vector<int>& vec, int b, int e) {
    if (b >= e) {
        return;
    }
    int idx = partion(vec, b, e);

    do_sort(vec, b, idx);
    do_sort(vec, idx + 1, e);
}

void quick_sort(std::vector<int>& vec) { do_sort(vec, 0, vec.size()); }