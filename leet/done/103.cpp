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
 * Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *  / \
 * 15  7
 * 
 * return its zigzag level order traversal as:
 *  [
 *       [3],
 *       [20,9],
 *       [15,7]
 *  ]
 */

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
        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            if (nullptr == root) {
                return ans;
            }

            queue<TreeNode*> q;
            q.push(root);
            bool reverse = false;

            while (!q.empty()) {
                int size = q.size(); 
                vector<int> level;
                for (int i=0; i<size; i++) {
                    auto it = q.front();
                    level.push_back(it->val);
                    q.pop();
                    if (it->left) q.push(it->left);
                    if (it->right) q.push(it->right);
                }
                if (reverse) {
                    std::reverse(level.begin(), level.end());
                }
                ans.push_back(level);
                reverse = !reverse;
            }

            return ans;
        }
};

namespace best {
    class Solution {
        public:
            vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
                vector<vector<int>> result;
                traverse(root, 1, result, true);
                return result;
            }

            void traverse(TreeNode *root, size_t level, vector<vector<int>> &result,
                    bool left_to_right) {
                if (!root) return;
                if (level > result.size())
                    result.push_back(vector<int>());
                if (left_to_right)
                    result[level-1].push_back(root->val);
                else
                    result[level-1].insert(result[level-1].begin(), root->val);
                traverse(root->left, level+1, result, !left_to_right);
                traverse(root->right, level+1, result, !left_to_right);
            }
    };
}

TEST(TestMine, HandleNoraml) {
    Solution s;
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node9 = new TreeNode(9);
    TreeNode* node20 = new TreeNode(20);
    TreeNode* node15 = new TreeNode(15);
    TreeNode* node7 = new TreeNode(7);

    node3->left = node9;
    node3->right = node20;
    node9->left = node15;
    node9->right = node7;

    std::vector<vector<int>> expect = {{3}, {20, 9}, {15, 7}};
    std::vector<vector<int>> ans = s.zigzagLevelOrder(node3);
    EXPECT_EQ(expect, ans);
}

#ifdef _TEST_
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
//Register the function as abenchmark
BENCHMARK_MAIN();   //程序入口
#endif

