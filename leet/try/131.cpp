#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
//
// 返回 s 所有可能的分割方案。
//
// 示例:
//
// 输入: "aab"
//输出:
//[
//  ["aa","b"],
//  ["a","a","b"]
//]
// Related Topics 深度优先搜索 动态规划 回溯算法

// leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<string>> partition(string s) {}
    std::vector<string> permute(string s) {
        std::vector<string> ans;
        std::function<void(int)> fn = [&fn, &ans, &s](int start) {
            if (start == s.size()) {
                ans.push_back(s);
                return;
            }

            for (int i = start; i < s.size(); i++) {
                std::swap(s[start], s[i]);
                fn(start + 1);
                std::swap(s[start], s[i]);
            }
        };

        fn(0);
        for (auto& x : ans) {
            std::cout << x << std::endl;
        }

        return ans;
    }
};
// leetcode submit region end(Prohibit modification and deletion)

TEST(TestSolution, HandlerNormal) {
    Solution s;
    s.permute("123");
}

static void BM_best(benchmark::State& state) {}

static void BM_mine(benchmark::State& state) {}

#ifdef _TEST_
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
// Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
#endif
