#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和
// nums2。请你找出并返回这两个正序数组的中位数。
// 进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？
//
// 示例 1：
// 输入：nums1 = [1,3], nums2 = [2]
//输出：2.00000
//解释：合并数组 = [1,2,3] ，中位数 2
//
// 示例 2：
// 输入：nums1 = [1,2], nums2 = [3,4]
//输出：2.50000
//解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
//
// 示例 3：
// 输入：nums1 = [0,0], nums2 = [0,0]
//输出：0.00000
//
// 示例 4：
// 输入：nums1 = [], nums2 = [1]
//输出：1.00000
//
// 示例 5：
// 输入：nums1 = [2], nums2 = []
//输出：2.00000
//
// 提示：
// nums1.length == m
// nums2.length == n
// 0 <= m <= 1000
// 0 <= n <= 1000
// 1 <= m + n <= 2000
// -106 <= nums1[i], nums2[i] <= 106
//
// Related Topics 数组 二分查找 分治算法

// leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    // Time： O(m+n), Space： O(m+n)
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() && nums2.empty()) {
            return 0;
        }

        std::vector<int> merged(nums1.size() + nums2.size(), 0);
        int i = 0;
        int j = 0;
        while (i < nums1.size() || j < nums2.size()) {
            if (i < nums1.size() && nums1[i] < nums2[j]) {
                merged[i + j] = nums1[i];
                i++;
            } else {
                merged[i + j] = nums2[j];
                j++;
            }
        }

        auto size = merged.size();
        if (size % 2) {
            return merged[size / 2];
        }

        auto mid = size / 2;
        return (merged[mid] + merged[mid - 1]) / 2.0;
    }

    // Time: O(m+n), Space: O(1)
    double findv2(vector<int>& nums1, vector<int>& nums2) {
        int i = 0;
        int j = 0;

        int target1 = (nums1.size() + nums2.size() + 1) / 2;
        int target2 = (nums1.size() + nums2.size() + 2) / 2;
        double ans = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
            if (i + 1 + j == target1) {
                std::cout << "first: i=" << i << " j=" << j << std::endl;
                if (i >= nums1.size()) {
                    ans = nums2[j] / 2.0 + ans;
                } else if (j >= nums2.size()) {
                    ans = nums1[i] / 2.0 + ans;
                } else {
                    ans = (nums1[i] > nums2[j] ? nums2[j] : nums1[i]) / 2.0 + ans;
                }
            }
            if (i + j + 1 == target2) {
                std::cout << "first: i=" << i << " j=" << j << std::endl;
                if (i >= nums1.size()) {
                    ans = nums2[j] / 2.0 + ans;
                } else if (j >= nums2.size()) {
                    ans = nums1[i] / 2.0 + ans;
                } else {
                    ans = (nums1[i] > nums2[j] ? nums2[j] : nums1[i]) / 2.0 + ans;
                }
            }
        }

        return ans;
    }

    double findV3(std::vector<int>& nums1, std::vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int left = (m + n + 1) / 2;
        int right = (m + n + 2) / 2;

        return (findKth(nums1, 0, nums2, 0, left) + findKth(nums1, 0, nums2, 0, right)) / 2.0;
    }

    int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
        if (i >= nums1.size())
            return nums2[j + k - 1];
        if (j >= nums2.size())
            return nums1[i + k - 1];
        if (k == 1)
            return min(nums1[i], nums2[j]);
        int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_MAX;
        int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_MAX;
        if (midVal1 < midVal2) {
            return findKth(nums1, i + k / 2, nums2, j, k - k / 2);
        } else {
            return findKth(nums1, i, nums2, j + k / 2, k - k / 2);
        }
    }
};
// leetcode submit region end(Prohibit modification and deletion)

TEST(TestSolution, HandlerNormal) {
    std::vector<int> nums1 = {1, 2, 5, 7};
    std::vector<int> nums2 = {3, 4, 6};
    Solution s;
    std::cout << s.findMedianSortedArrays(nums1, nums2) << std::endl;
    std::cout << s.findv2(nums1, nums2) << std::endl;
    std::cout << s.findV3(nums1, nums2) << std::endl;
}

static void BM_best(benchmark::State& state) {}

static void BM_mine(benchmark::State& state) {}

#ifdef _TEST_
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
// Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
#endif
