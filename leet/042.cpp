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
        int trap(vector<int>& height) {
            int left_max = 0;
            int right_max = 0;
            int ans = 0;
            for (int i=0; i<height.size(); i++) {
                left_max = 0;
                right_max = 0;
                for (int j=i-1; j>=0; j--) {
                    if (left_max < height[j]) {
                        left_max = height[j];
                    }
                }
                for (int j=i+1; j<height.size(); j++) {
                    if (right_max < height[j]) {
                        right_max = height[j];
                    }
                }

                if (height[i] < left_max && height[i] < right_max) {
                    ans += (left_max > right_max ? right_max : left_max) - height[i];
                }
            }

            return ans;
        }
};

TEST(TestSolution, HandlerNormal) {
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    Solution s;
    int ans = s.trap(height);
    EXPECT_EQ(6, ans);
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

