/*
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。

示例: 
输入: s = 7, nums = [2,3,1,2,4,3]
输出: 2
解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。
*/
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
        int minSubArrayLen(int s, vector<int>& nums) {
        }

};

int main(int argc, const char** argv) {
    Solution s;
    
    vector<int> nums = {2,3,1,2,4,3,5};
    cout << s.minSubArrayLen(7, nums) << endl;
    cout << s.minSubArrayLen(9, nums) << endl;
    cout << s.minSubArrayLen(10, nums) << endl;
    vector<int> nums2 = {1, 4, 4};
    cout << s.minSubArrayLen(7, nums2) << endl;
}
