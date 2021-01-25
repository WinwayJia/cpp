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
    int uniquePaths(int m, int n) {
        vector<vector<int>> vec(n, vector<int>(m, 0));
        for (int i=1; i<m; i++) {
            vec[0][i] = 1;
        }
        for (int i=1; i<n; i++) {
            vec[i][0] = 1;
        }

        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                vec[j][i] = vec[j][i-1] + vec[j-1][i];
            }
        }

        return vec[n-1][m-1];
    }
};

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        EXPECT_EQ(3, s.uniquePaths(3, 2));
    }
    {
        EXPECT_EQ(28, s.uniquePaths(7, 3));
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

