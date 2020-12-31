#include <iostream>
#include <vector>
#include "util.h"

void select_sort(std::vector<int>& vec) {
    for (int i=0; i<vec.size()-1; i++) {
        int idx = i;
        for (int j=i+1; j<vec.size(); j++) {
            if (vec[idx] > vec[j]) {
                idx = j;
            } 
        }

        if (idx != i) {
            swap(vec, i, idx);
        }
    }
}

int main() {
    std::vector<int> vec = {3,2,1,5,4};
    std::cout<<vec<< std::endl;
//    select_sort(vec);
    // bubble_sort(vec);
    quick_sort(vec);
    std::cout<<vec<< std::endl;
}
