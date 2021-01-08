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
/*
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 * Example 1:
 * Input:
 *     2
 *    / \
 *   1   3
 * Output: true
 *
 * Example 2:
 *
 *     5
 *    / \
 *   1   4
 *      / \
 *     3   6
 * Output: false
 * Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
 *              is 5 but its right child's value is 4.
 */

/**
 *  * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        bool isValidBST(TreeNode* root) {
            if (nullptr == root) {
                return true;
            }
            deque<pair<TreeNode*, int>> d;
            d.push_front(make_pair(root, 0));
            int last;
            int isFirst = true;

            while (!d.empty()) {
                auto it = d.front();
                d.pop_front();

                if (1 == it.second) {
                    cout << it.first->val << endl;
                    if (true == isFirst) {
                        isFirst = false;
                        last = it.first->val;
                    } else {
                        if (it.first->val < last) {
                            return false;
                        }
                        last = it.first->val;
                    }
                } else {
                    if (it.first->right) {
                        d.push_front(make_pair(it.first->right, 0));
                    }
                    d.push_front(make_pair(it.first, 1));
                    if (it.first->left) {
                        d.push_front(make_pair(it.first->left, 0));
                    }
                }
            }
            return true;
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
        EXPECT_EQ(false, s.isValidBST(node1));
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
        EXPECT_EQ(true, s.isValidBST(node2));
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

