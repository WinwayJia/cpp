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
        int rob(vector<int>& nums) {
            if (nums.size() <= 0) {
                return 0;
            }
            if (1 == nums.size()) {
                return nums[0];
            }
            if (2 == nums.size()) {
                return nums[1] > nums[0] ? nums[1] : nums[0];
            }

            vector<int> ans(nums.size());
            ans[0] = nums[0];
            ans[1] = nums[1] > nums[0] ? nums[1] : nums[0];
            for (int i=2; i<nums.size(); i++) {
                ans[i] = std::max(ans[i-1], ans[i-2]+nums[i]);
            }
            return ans[nums.size()-1];
        }
};


TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        vector<int> nums = {2,7,9,3,1};
        EXPECT_EQ(s.rob(nums), 12);
    }
    {
        vector<int> nums = {1,2,3,1};
        EXPECT_EQ(s.rob(nums), 4);
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

