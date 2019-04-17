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
    int removeDuplicates(vector<int>& nums) {
        int ans = 0;
        for (int i=0; i<nums.size(); i++) {
            int len = 0;
            for (int j=i+1; j<nums.size(); j++) {
                if (nums[i] != nums[j]) {
                    break;
                }
                len ++;
            }
            nums[ans] = nums[i];
            ans ++;
            i += len;
        }
        return ans;
    }
};

static void BM_best(benchmark::State& state) {
}

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        vector<int> nums = {1, 1, 2, 2};
        EXPECT_EQ(2, s.removeDuplicates(nums));
        EXPECT_EQ(nums[0], 1);
        EXPECT_EQ(nums[1], 2);
    }
    {
        vector<int> nums = {1, 1, 1};
        EXPECT_EQ(1, s.removeDuplicates(nums));
        EXPECT_EQ(nums[0], 1);
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

