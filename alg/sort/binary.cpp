#include "util.h"

int binary_search(const std::vector<int>& vec, int target) {
    int low = 0;
    int high = vec.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (vec[mid] == target) {
            return mid;
        }

        if (vec[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}