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
    int lengthOfLastWord(string s) {
        int ans = 0;
        bool flag = true;
        for (int i=s.size()-1; i>=0; i--) {
            if (flag) {
                if (' ' != s[i]) {
                    ans += 1;
                } else {
                    break;
                }
            } else {
                if (' ' != s[i]) {
                    flag = true;
                    ans += 1;
                }
            }
        }

        return ans;
    }
};

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        string str = "a ";
        EXPECT_EQ(1, s.lengthOfLastWord(str))
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

