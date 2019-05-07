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
#include <queue>
#include <stack>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

using namespace std;

/*
 * 2: abc
 * 3: def
 * 4: ghi
 * 5: jkl
 * 6: mno
 * 7: pqrs
 * 8: tuv
 * 9: wxyz
 */
/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Example:
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:
Although the above answer is in lexicographical order, your answer could be in any order you want.
*/

class Solution {
    public:
        void dfs(int step, vector<char> nums, const string& digits, vector<string>& ans, const map<char, vector<char>>& mapping) {
            if (digits.size() == step) {
                string tmp;
                for (auto x : nums) {
                    tmp += x;
                }
                ans.push_back(tmp);
                return;
            }

            const auto& vec = mapping.find(digits[step]);
            for (auto x : vec->second) {
                nums[step] = x;
                dfs(step+1, nums, digits, ans, mapping);
            }
        }

        vector<string> letterCombinations(string digits) {
            vector<string> ans;
            if (digits.empty()) {
                return ans;
            }
            map<char, vector<char>> mapping = {
                { '2', {'a', 'b', 'c'} },
                { '3', {'d', 'e', 'f'} },
                { '4', {'g', 'h', 'i'} },
                { '5', {'j', 'k', 'l'} },
                { '6', {'m', 'n', 'o'} },
                { '7', {'p', 'q', 'r', 's'} },
                { '8', {'t', 'u', 'v'} },
                { '9', {'w', 'x', 'y', 'z'} }
            };

            vector<char> nums(digits.size());
            dfs(0, nums, digits, ans, mapping);

            return ans;
        }
};


TEST(TestSolution, HandlerNormal) {
    Solution s;
    auto ans = s.letterCombinations("233");
}

static void BM_best(benchmark::State& state) {
}

static void BM_mine(benchmark::State& state) {
}

#ifdef _TEST_
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
    //Register the function as abenchmark
    BENCHMARK(BM_mine); //用于注册测试函数
    BENCHMARK(BM_best); //用于注册测试函数
    BENCHMARK_MAIN();   //程序入口
#endif

