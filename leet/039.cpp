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
    void backtrack(const vector<int>& candidates, vector<int>& solu, vector<vector<int>>& ans, int target, int start) {
        if (target < 0) {
            return;
        }

        if (0 == target) {
            ans.push_back(solu);
            return;
        }

        for (int i=start; i<candidates.size(); i++) {
            solu.push_back(candidates[i]);
            backtrack(candidates, solu, ans, target-candidates[i], i);
            solu.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> solu;
        backtrack(candidates, solu, ans, target, 0);

        return ans;
    }
};

TEST(TestSolution, HandlerNormal) {
    auto print = [](const vector<int>& vec) {
        const char* sep = "";
        for (auto x : vec) {
            cout << sep << x ;
            sep = ", ";
        }
        cout << endl;
    };

    Solution s;
    {
        vector<int> candidates{2,3,6,7};
        auto ans = s.combinationSum(candidates, 7);
        for (auto& solu : ans) {
            print(solu);
        }
    }{
        vector<int> candidates{2,3,5};
        auto ans = s.combinationSum(candidates, 8);
        for (auto& solu : ans) {
            print(solu);
        }
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

