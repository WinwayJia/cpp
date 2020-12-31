#include <iostream>
#include <vector>

int change(std::vector<int> &vec, int total) {
    std::vector<int> table(total + 1, 0);

    for (auto x : vec) {
        table[x] = 1;
    }

    for (int i = 1; i < table.size(); i++) {
        int min = INT32_MAX;
        int tmp = -1;
        if (0 == table[i]) {
            for (auto x : vec) {
                if (i > x) {
                    tmp = table[i - x] + 1;
                    min = min > tmp ? tmp : min;
                }
            }
            if (min == INT32_MAX) {
                return -1;
            }
            table[i] = min;
        }
    }

    return table.back();
}

int main(int argc, char const *argv[]) {
    std::vector<int> coins = {1, 20, 2, 5, 10};
    // std::cout << change(coins, 2) << std::endl;
    // std::cout << change(coins, 12) << std::endl;
    // std::cout << change(coins, 16) << std::endl;
    std::cout << change(coins, 20) << std::endl;
    std::cout << change(coins, 25) << std::endl;
    std::cout << change(coins, 26) << std::endl;
    return 0;
}
