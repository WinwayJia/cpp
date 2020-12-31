#include <vector>
#include "util.h"

void bubble_sort(std::vector<int>& vec) {
    for (int i=0; i<vec.size(); i++) {
        for (int j=0; j<vec.size()-i-1; j++) {
            if (vec[j] > vec[j+1]) {
                swap(vec, j, j+1);
            }
        }
    }
}
