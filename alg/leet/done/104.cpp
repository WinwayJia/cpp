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
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        int maxDepth(TreeNode* root) {
            int ans = 0;
            if (nullptr == root) {
                return ans;
            }
            ans = std::max(maxDepth(root->left), maxDepth(root->right)) + 1;

            return ans;
        }
};

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        TreeNode* node1 = new TreeNode(1);
        TreeNode* node2 = new TreeNode(2);
        TreeNode* node3 = new TreeNode(3);
        node1->left = node2;
        node1->right = node3;
        EXPECT_EQ(2, s.maxDepth(node1));
        delete node1;
        delete node2;
        delete node3;
    }
    {
        cout << "new test" << endl;
        TreeNode* node1 = new TreeNode(1);
        TreeNode* node2 = new TreeNode(2);
        TreeNode* node3 = new TreeNode(3);
        node2->left = node1;
        node1->right = node3;
        EXPECT_EQ(3, s.maxDepth(node2));
        delete node1;
        delete node2;
        delete node3;
    }
}

static void BM_best(benchmark::State& state) {
}

static void BM_mine(benchmark::State& state) {
}

#ifdef _TEST_
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
//Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
#endif

