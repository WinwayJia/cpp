/*
 * 给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。
 * 你可以假设数组是非空的，并且给定的数组总是存在众数。
 *
 * 示例 1:
 * 输入: [3,2,3]
 * 输出: 3
 * 示例 2:
 *
 * 输入: [2,2,1,1,1,2,2]
 * 输出: 2
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
        int majorityElement(vector<int>& nums) {
            map<int, int> s;
            int result;
            int count = 0;
            for (auto n : nums) {
                count = 1;
                auto it = s.insert(map<int, int>::value_type(n, 1));
                if (it.second == false) {
                    count = it.first->second + 1;
                    it.first->second = count;
                }
                if (count > nums.size()/2) {
                    result = n;
                    break;
                }
            }
            return result;
        }
};


int main(int argc, const char** argv) {
    Solution s;

    vector<int> nums = {2,2,1,1,1,2,2};
    cout << s.majorityElement(nums) << endl;

    vector<int> nums2 = {1,1,1,2,2};
    cout << s.majorityElement(nums2) << endl;
}
