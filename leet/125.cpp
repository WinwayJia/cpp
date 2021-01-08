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

//给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
//
// 说明：本题中，我们将空字符串定义为有效的回文串。
//
// 示例 1:
//
// 输入: "A man, a plan, a canal: Panama"
//输出: true
//
//
// 示例 2:
//
// 输入: "race a car"
//输出: false
//
// Related Topics 双指针 字符串

// leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool isPalindrome(string s) {
        if (s.empty()) {
            return true;
        }

        auto needCheckAndUpper = [](char& c) -> bool {
            if (c >= '0' && c < '9') {
                return true;
            }
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
                return true;
            }
            if (c >= 'A' && c < 'Z') {
                return true;
            }

            return false;
        };

        int start = 0;
        int stop = s.size() - 1;

        while (start <= stop) {
            if (!needCheckAndUpper(s[start])) {
                start++;
                continue;
            }
            if (!needCheckAndUpper(s[stop])) {
                stop--;
                continue;
            }

            if (s[start] != s[stop]) {
                return false;
            } else {
                start++;
                stop--;
            }
        }

        return true;
    }
};
// leetcode submit region end(Prohibit modification and deletion)

TEST(TestSolution, HandlerNormal) {
    Solution s;
    std::string str = "A man, a plan, a canal: Panama";
    std::cout << s.isPalindrome(str) << std::endl;
    std::cout << s.isPalindrome("race a car") << std::endl;
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
