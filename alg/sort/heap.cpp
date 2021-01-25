#include "util.h"
static inline int left(int pos) { return (pos << 1) + 1; }
static inline int right(int pos) { return (pos << 1) + 2; }

void heapify(std::vector<int>& vec, int pos, int len) {
    int idx = pos;
    if (left(pos) < len && vec[left(pos)] > vec[idx]) {
        idx = left(pos);
    }

    if (right(pos) < len && vec[right(pos)] > vec[idx]) {
        idx = right(pos);
    }

    if (idx != pos) {
        std::swap(vec[pos], vec[idx]);
        heapify(vec, idx, len);
    }
}

void build_heap(std::vector<int>& vec) {
    int pos = vec.size() / 2;
    while (pos >= 0) {
        heapify(vec, pos, vec.size());
        pos--;
    }
}

void heap_sort(std::vector<int>& vec) {
    build_heap(vec);

    std::cout << "heaped: " << vec << std::endl;

    for (auto i = 0; i < vec.size(); i++) {
        std::swap(vec[0], vec[vec.size() - i - 1]);
        heapify(vec, 0, vec.size() - i - 1);
    }
}