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

/*
 * Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? 
 * Find all unique triplets in the array which gives the sum of zero.
 *
 * Note:
 * The solution set must not contain duplicate triplets.
 *
 * Example:
 *
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 *
 * A solution set is:
 * [
 *   [-1, 0, 1],
 *   [-1, -1, 2]
 * ]
 */ 

class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> ans;
            map<int, vector<pair<int, int>>> m;
            for (int i=0; i<nums.size()-1; i++) {
                for (int j=i+1; j<nums.size(); j++) {
                    vector<pair<int, int>> item = {pair<int, int>{i, j}};
                    auto ret = m.insert(make_pair(nums[i]+nums[j], item));
                    if (ret.second == false) {
                        vector<pair<int, int>>& pairs = ret.first->second;
                        bool existed = false;
                        for (auto& x : pairs) {
                            if ((nums[x.first] == nums[i] && nums[x.second] == nums[j]) || 
                                (nums[x.second] == nums[i] && nums[x.first] == nums[j])) {
                                existed = true;
                                break;
                            }
                        }
                        if (false == existed) {
                            ret.first->second.push_back(pair<int, int>(i, j));
                        }
                    }
                }
            }

            for (int i=0; i<nums.size(); i++) {
                auto it = m.find(0-nums[i]);
                if (it == m.end()) {
                    continue;
                }
                for (auto& p : it->second) {
                    if (p.first == i || p.second == i) {
                        continue;
                    }
                    ans.push_back({nums[p.first], nums[p.second], nums[i]});
                }
            }
            
            return ans;
        }
};


TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        vector<int> nums =  {-1, 0, 1, 2, -1, -4};
        auto&& ans = s.threeSum(nums);
        for (auto& row : ans) {
            for (auto i : row) {
                cout << i << " ";
            }
            cout << endl;
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

