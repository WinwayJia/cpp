/*
 * 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 说明：解集不能包含重复的子集。
 * 示例:
 * 输入: nums = [1,2,3]
 * 输出:
 * [
 *  [3],
 *  [1],
 *  [2],
 *  [1,2,3],
 *  [1,3],
 *  [2,3],
 *  [1,2],
 *  []
 * ]
 */
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

using namespace std;

class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            vector<vector<int>> res;
            vector<int> res_sub;
            res.push_back(res_sub);
            generate(nums, 0, res, res_sub);

            return res;
        }

        void generate(vector<int>& nums, int start, vector<vector<int>>& res, vector<int>& res_sub) {
            if (start >= nums.size()) {
                return;
            }
            for (int i = start; i < nums.size(); i++) {
                res_sub.push_back(nums[i]);
                res.push_back(res_sub);
                generate(nums, i + 1, res, res_sub);
                res_sub.pop_back();
            }
        }
};


int main(int argc, const char** argv) {
    Solution s;

    vector<int> nums = {1, 2, 3};
    auto ret = s.subsets(nums);

    return 0;
}
