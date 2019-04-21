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

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ans;
        if (nullptr == root) {
            return ans;
        }
        stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            auto t = s.top();
            s.pop();
            if (t->right) {
                s.push(t->right);
            }
            if (t->left) {
                s.push(t->left);
            }
            if (nullptr == t->left && nullptr == t->right) {
                ans.push_back(t->val);
            }
        }
        return ans;
    }
};

TEST(TestSolution, HandlerNormal) {
}

static void BM_best(benchmark::State &state) {
}

static void BM_mine(benchmark::State &state) {
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
