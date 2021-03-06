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
        vector<int> searchRange(vector<int>& nums, int target) {
            vector<int> ans= {-1, -1};
            for (int i=0; i<nums.size(); i++) {
                if (nums[i] < target) {
                    continue;
                } else if (nums[i] > target) {
                    return ans;
                } else {
                    nums[0] == -1 ?  ans[0] = i : ans[1] = i;
                }
            }

            return ans;
        }
};


TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
    }
    {
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

