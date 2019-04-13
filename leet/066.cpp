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
    vector<int> plusOne(vector<int>& digits) {
        vector<int> ans;
        int flag = 1;
        int tmp;
        for (int i=digits.size()-1; i>=0; i--) {
            tmp = digits[i] + flag;
            if (tmp >= 10) {
                flag = 1;
                tmp -= 10;
            } else {
                flag = 0;
            }
            ans.push_back(tmp);
        }
        if (flag) {
            ans.push_back(flag);
        }

        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

static void BM_best(benchmark::State& state) {
}

TEST(TestMine, HandleNoraml) {
    Solution s;
    {
        vector<int> input = {1, 2, 3};
        vector<int> ans = {1, 2, 4};
        EXPECT_EQ(ans, s.plusOne(input));
    }
    {
        vector<int> input = {1, 2, 3, 9};
        vector<int> ans = {1, 2, 4, 0};
        EXPECT_EQ(ans, s.plusOne(input));
    }
    {
        vector<int> input = {0};
        vector<int> ans = {1};
        EXPECT_EQ(ans, s.plusOne(input));
    }
    {
        vector<int> input = {9, 9};
        vector<int> ans = {1, 0, 0};
        EXPECT_EQ(ans, s.plusOne(input));
    }
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

