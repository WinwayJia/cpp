/*
 * 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
 *
 * 示例 1:
 * 输入: coins = [1, 2, 5], amount = 11
 * 输出: 3 
 * 解释: 11 = 5 + 5 + 1
 *
 * 示例 2:
 * 输入: coins = [2], amount = 3
 * 输出: -1
 *
 * 说明: 你可以认为每种硬币的数量是无限的。
 */
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        int coinChange(vector<int>& coins, int amount) {
            vector<int> dp(amount+1, amount+1);
            dp[0] = 0;

            for (int i=0; i<=amount; i++) {
                for (auto c : coins) {
                    if (c <= i) {
                        dp[i] = min(dp[i-c]+1, dp[i]);
                    }
                }
            }
            return dp.back() > amount ? -1 : dp.back();
        }
};

int main(int argc, const char** argv) {
    Solution s;

    vector<int> coins = {1, 2, 5};

    cout << s.coinChange(coins, 11) << endl;
    cout << s.coinChange(coins, 100) << endl;
    cout << s.coinChange(coins, 1) << endl;
}
