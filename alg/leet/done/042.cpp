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

        int trap2(vector<int>& height) {
            vector<int> left_max(height.size());
            vector<int> right_max(height.size());
            int ans = 0;

            int max = height[0];
            for (int i=1; i<height.size()-1; i++) {
                left_max[i] = max;
                if (max < height[i]) {
                    max = height[i];
                }
            }
            max = height[height.size()-1];
            for (int i=height.size()-1; i>0; i--) {
                right_max[i] = max;
                if (max < height[i]) {
                    max = height[i];
                }
            }

            for (int i=1; i<height.size(); i++) {
                if (height[i] < left_max[i] && height[i] < right_max[i]) {
                    ans += (left_max[i] > right_max[i] ? right_max[i] : left_max[i]) - height[i];
                }
            }
            return ans;
        }

        int trap3(vector<int>& height) {
            int left_max = 0;
            int right_max = 0;
            int ans = 0;
            int left = 0;
            int right = height.size() - 1;

            while (left < right) {
                if (height[left] < height[right]) {
                    if (height[left] < left_max) {
                        ans += left_max - height[left];
                    } else {
                        left_max = height[left];
                    }
                    left ++;
                } else {
                    if (height[right] < right_max) {
                        ans += right_max - height[right];
                    } else {
                        right_max = height[right];
                    }
                    right --;
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

    int ans2 = s.trap2(height);
    EXPECT_EQ(6, ans2);

    int ans3 = s.trap3(height);
    EXPECT_EQ(6, ans3);
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

