/*
   给定两个大小为 m 和 n 的有序数组 nums1 和 nums2 。
   请找出这两个有序数组的中位数。要求算法的时间复杂度为 O(log (m+n)) 。

   示例 1:
   nums1 = [1, 3]
   nums2 = [2]

   中位数是 2.0
   示例 2:
   nums1 = [1, 2]
   nums2 = [3, 4]

   中位数是 (2 + 3)/2 = 2.5
   */
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using namespace std;

class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            vector<int> merge;
            int i,j;
            for(i=0,j=0; i<nums1.size() && j<nums2.size();) {
                if (nums1[i] > nums2[j]) {
                    merge.push_back(nums2[j]);
                    j++;
                } else {
                    merge.push_back(nums1[i]);
                    i++;
                }
            }
            int pos; 
            vector<int>* left = nullptr;
            if (i < nums1.size()) {
                left = &nums1;
                pos = i;
            } 
            if (j < nums2.size()) {
                left = &nums2;
                pos = j;
            }

            int length = merge.size() + left->size() - pos;
            assert(length == nums1.size() + nums2.size());
            if (length % 2 == 0) {
                int h = length / 2;
                int l = h - 1;
                int hv;
                int lv;
                if (h < merge.size()) {
                    hv = merge[h];
                } else {
                    hv = (*left)[h-merge.size()+pos];
                }
                if (l < merge.size()) {
                    lv = merge[l];
                } else {
                    lv = (*left)[l-merge.size()+pos];
                }
                return (hv+lv)/2.0;
            } else {
                int mid = length / 2;
                if (mid < merge.size()) {
                    return merge[mid];
                } else {
                    return (*left)[mid-merge.size()+pos];
                }
            }
        }
};

int main(int argc, const char** argv) {
    Solution s;
    vector<int> nums1 = {1, 2};
    vector<int> nums2 = {3, 4};
    
    cout << s.findMedianSortedArrays(nums1, nums2) << endl;
}
