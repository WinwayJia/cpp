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

//给定一个非负整数数组，你最初位于数组的第一个位置。
//
// 数组中的每个元素代表你在该位置可以跳跃的最大长度。
//
// 判断你是否能够到达最后一个位置。
//
// 示例 1:
//
// 输入: [2,3,1,1,4]
//输出: true
//解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
//
//
// 示例 2:
//
// 输入: [3,2,1,0,4]
//输出: false
//解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ，
//所以你永远不可能到达最后一个位置。
//
// Related Topics 贪心算法 数组
// 👍 993 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        std::vector<int> reachable(nums.size());
        reachable[0] = 1;

        for (int i = 0; i < nums.size(); i++) {
            if (0 == reachable[i]) {
                break;
            }
            for (int j = 1; j <= nums[i]; j++) {
                if (i + j >= nums.size()) {
                    return true;
                }
                reachable[i + j] = 1;
            }
        }

        return reachable[reachable.size() - 1] == 1;
    }
};
// leetcode submit region end(Prohibit modification and deletion)

TEST(TestSolution, HandlerNormal) {
    Solution s;
    std::vector<std::vector<int>> vec = {
        {2, 3, 1, 1, 4},
        {3, 2, 1, 0, 4},
    };
    for (auto& v : vec) {
        std::cout << s.canJump(v) << std::endl;
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
