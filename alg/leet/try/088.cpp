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

//给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
// 说明：
// 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
// 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
//
// 示例：
//输入：
// nums1 = [1,2,3,0,0,0], m = 3
// nums2 = [2,5,6],       n = 3
//输出：[1,2,2,3,5,6]
//
//
// 提示：
// -10^9 <= nums1[i], nums2[i] <= 10^9
// nums1.length == m + n
// nums2.length == n
//
// Related Topics 数组 双指针

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        while (m > 0 && n > 0) {
            if (nums1[m - 1] > nums2[n - 1]) {
                nums1[m + n - 1] = nums1[m - 1];
                m--;
            } else {
                nums1[m + n - 1] = nums2[n - 1];
                n--;
            }
        }

        while (n > 0) {
            nums1[n - 1] = nums2[n - 1];
            n--;
        }
    }
};

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    for (auto x : vec) {
        out << x << " ";
    }
    return out;
}

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
        std::vector<int> nums2 = {2, 5, 6};
        s.merge(nums1, 3, nums2, 3);
        std::cout << nums1 << std::endl;
    }
    {
        std::vector<int> nums1 = {1, 2, 3, 0, 0, 0, 0, 0};
        std::vector<int> nums2 = {-1, 0, 2, 5, 6};
        s.merge(nums1, 3, nums2, 5);
        std::cout << nums1 << std::endl;
    }
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
