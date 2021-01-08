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

class Solution
{
public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> ans;
        if (nums.size() == 1)
        {
            ans.push_back({nums[0]});
            return ans;
        }
        if (2 == nums.size())
        {
            ans.push_back({nums[0], nums[1]});
            ans.push_back({nums[1], nums[0]});
            return ans;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            std::swap(nums[0], nums[i]);
            vector<int> in(nums.begin() + 1, nums.end());
            auto &&ret = permute(in);
            for (auto &x : ret)
            {
                x.push_back(nums[0]);
            }
            std::copy(ret.begin(), ret.end(), std::back_inserter(ans));
        }
        return ans;
    }
};

class SolutionBest
{
public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        if (nums.empty()) {
            return vector<vector<int>>{{}};
        }

        vector<vector<int>> res;
        helper(res, nums, 0);
        return res;
    }

    void helper(vector<vector<int>> &res, vector<int> &nums, int begin)
    {
        if (begin == nums.size()) {
            res.push_back(nums);
            return;
        }

        for (int i = begin; i < nums.size(); i++) {
            swap(nums[i], nums[begin]);
            helper(res, nums, begin + 1);
            swap(nums[i], nums[begin]);
        }
    }
};

TEST(TestSolution, HandlerNormal)
{
    Solution s;
    SolutionBest b;
    {
        vector<int> nums = {1, 2, 3};
        auto && ans = s.permute(nums);
        auto && bans = b.permute(nums);
        auto print = [](decltype(ans)& ans){
            for (auto & r : ans) {
                for (auto n : r) {
                    cout << n << " ";
                }
                cout << endl;
            }
        };
        print(ans);
        cout << "\n\n";
        print(bans);
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
