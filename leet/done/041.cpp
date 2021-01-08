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
        int firstMissingPositive(vector<int>& nums) {
            vector<int> arr(nums.size(), 0);
            for (auto i : nums) {
                if (i <= nums.size() && i > 0) {
                    arr[i-1] = 1;
                }
            }

            for (int i=0; i<arr.size(); i++) {
                if (arr[i] == 0) {
                    return i + 1;
                }
            }
            return nums.size() + 1;
        }
};


TEST(TestSolution, HandlerNormal) {
    Solution s;
    int ans;
    {
        vector<int> arr = {1,2,3};
        ans = s.firstMissingPositive(arr);
        EXPECT_EQ(ans, 4);
    }
    {
        vector<int> arr = {3,4,-1,1};
        ans = s.firstMissingPositive(arr);
        EXPECT_EQ(ans, 2);
    }
    {
        vector<int> arr = {7,8,9,11,12};
        ans = s.firstMissingPositive(arr);
        EXPECT_EQ(ans, 1);
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

