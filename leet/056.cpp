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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1) {
            return intervals;
        }

        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& x, const vector<int>& y) -> bool {
            if (x[0] < y[0]) {
                return true;
            }
            if (x[0] > y[0]) {
                return false;
            }

            return x[1] < y[1];
        });

        vector<vector<int>> ans{intervals[0]};
        for (int i=1; i<intervals.size(); i++) {
            vector<int>& back = ans.back();
            if (back[1] < intervals[i][0]) {
                ans.push_back(intervals[i]);
                continue;
            }

            if (back[1] > intervals[i][1]) {
                continue;
            }
            back[1] = intervals[i][1];
        }

        return ans;
    }
};


TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        vector<vector<int>> intervals{{1,2},{1,3},{4,9},{5,7}};
        auto ans = s.merge(intervals);
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

