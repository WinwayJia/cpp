/*
 * 在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 *
 * 示例 1:
 *
 * 输入: [3,2,1,5,6,4] 和 k = 2
 * 输出: 5
 * 示例 2:
 *
 * 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
 * 输出: 4
 * 说明:
 *
 * 你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。
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
        int partation(vector<int>& nums, int b, int e) {
            int i = b + 1;
            int j = b + 1;
            for (; i<e; i++) {
                if (nums[i] > nums[b]) {
                    swap(nums[i], nums[j]);
                    j++;
                }
            }
            swap(nums[j-1], nums[b]);

            return j-1;
        }

        int theK(vector<int>& nums, int b, int e, int k) {
            int ret = partation(nums, b, e);
            if (ret+1 == k) {
                return nums[ret];
            } else if (ret+1 < k) {
                return theK(nums, ret+1, e, k);
            } else {
                return theK(nums, b, ret, k);
            }
        }

        int findKthLargest(vector<int>& nums, int k) {
            return theK(nums, 0, nums.size(), k);
        }


        ////////////////////////////////////////////////
        inline int LEFT(int k) {
            return k * 2 + 1;
        }
        inline int RIGHT(int k) {
            return k * 2 + 2;
        }
        void heapify(vector<int>& nums, int k) {
            int index = k;
            int left = LEFT(k);
            int right = RIGHT(k);

            if (left < nums.size() && nums[index] < nums[left]) {
                index = left;
            } 
            if (right < nums.size() && nums[index] < nums[right]) {
                index = right;
            }

            if (index != k) {
                swap(nums[k], nums[index]);
                heapify(nums, index);
            }
        }

        void makeHeap(vector<int>& nums) {
            for (int i=nums.size()/2; i>=0; i--) {
                heapify(nums, i);
            }
        }

        int TopK(vector<int>& nums, int k) {
            makeHeap(nums[:]);

        }
};


int main(int argc, const char** argv) {
    Solution s;

    vector<int> vec = {0,3,2,1,5,6,4,7,8};
    //    cout << s.partation(vec) << endl;
    //    cout << s.findKthLargest(vec, 4) << endl;
    s.makeHeap(vec);

    return 0;
}
