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

class Solution {
    public:
        int myAtoi(string str) {
            int ans = 0;
            bool began = false;
            bool neg = false;
            int div = INT_MAX / 10;
            for (auto c : str) {
                if (c == '-' || c == '+') {
                    if (began == true) {
                        break;
                    }
                    began = true;
                    if ('-' == c) {
                        neg = true;
                    }
                    continue;
                }
                if (c >= '0' && c <= '9') {
                    began = true;
                    int dig = c - '0';
                    if (ans < div || (ans == div && dig < 8)) {
                        ans = ans * 10 + c - '0';
                    } else {
                        return neg ? INT_MIN : INT_MAX;
                    }
                    continue;
                } 

                if (began == false && c == ' ') {
                    continue;
                }

                if (c > '0' || c > '9') {
                    break;
                }
            }
            return neg ? 0 - ans : ans;
        }
};

TEST(TestSolution, HandlerNormal) {
    string str = "42";
    Solution s;
    EXPECT_EQ(42, s.myAtoi(str));

    str = "   -42";
    EXPECT_EQ(-42, s.myAtoi(str));
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

