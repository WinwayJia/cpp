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
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为1000。
 *
 * 示例 1：
 * 输入: "babad"
 * 输出: "bab"
 * 注意: "aba"也是一个有效答案。
 *
 * 示例 2：
 * 输入: "cbbd"
 * 输出: "bb"
 */





















class Solution {
    public:
        struct Pos {
            Pos() : begin(0), end(0){}
            int begin;
            int end;
        };
        string longestPalindrome(string s) {
            std::vector<Pos> dp(s.size());
            for (size_t i=0; i<s.size(); i++) {
                if (i > 0 && s[i] == s[i-1]) {
                    dp[i].begin = i-1;
                    dp[i].end = i;
                } else {
                    dp[i].begin = i;
                    dp[i].end = i;
                }
                int idx = -1;
                for (size_t j=0; j<=i; j++) {
                    int begin = dp[j].begin;
                    int end = dp[j].end;
                    if (begin > 0 && end + 1 == i 
                        && s[begin-1] == s[i]) {
                        if (-1 == idx) {
                            idx = j;
                        } else {
                            if (end - begin > dp[idx].begin - dp[idx].end) {
                                idx = j;
                            }
                        }
                    }
                }
                if (idx != -1) {
                    dp[i].begin = dp[idx].begin - 1;
                    dp[i].end = dp[idx].end + 1;
                }
            }

            Pos ans;
            for (auto& p : dp) {
                if (p.end - p.begin > ans.end - ans.begin) {
                    ans = p;
                }
            }

            return s.substr(ans.begin, ans.end-ans.begin+1);
        }
};

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        std::string str = "babad";
        auto ans = s.longestPalindrome(str);
        std::cout << ans << std::endl;
    }
    {
        std::string str = "abbad";
        auto ans = s.longestPalindrome(str);
        std::cout << ans << std::endl;
    }
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

