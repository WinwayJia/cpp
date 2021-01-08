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
        bool isSameTree(TreeNode* p, TreeNode* q) {
            if (nullptr == p && nullptr == q) {
                return true;
            }

            if ((nullptr != p && nullptr == q) || (nullptr == p && nullptr != q)) {
                return false;
            }

            if (p->val != q->val) {
                return false;
            }

            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
        EXPECT_EQ(true, s.isSameTree(node1, node1));
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
        node2->right = node3;
        EXPECT_EQ(true, s.isSameTree(node2, node2));
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

