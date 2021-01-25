/*
   给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。

   说明:
   初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
   你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
   示例:

   输入:
   nums1 = [1,2,3,0,0,0], m = 3
   nums2 = [2,5,6],       n = 3

   输出: [1,2,2,3,5,6]
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
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            int pos = m + n - 1;
            int n1 = m -1;
            int n2 = n -1;
            while (n1 >= 0 && n2 >= 0) {
                if (nums1[n1] > nums2[n2]) {
                    nums1[pos--] = nums1[n1--];
                } else {
                    nums1[pos--] = nums2[n2--];
                }
            }
            while (n2 >= 0) {
                nums1[pos--] = nums2[n2--];
            }
        }
};


int main(int argc, const char** argv) {
    Solution s;
    vector<int> nums1 = {1,2,3,0,0,0};
    int m = 3;
    vector<int> nums2 = {2,5,6};
    int n = 3;

    s.merge(nums1, m, nums2, n);
    for (auto a : nums1) {
        cout << a << " ";
    }
    cout << endl;
}
