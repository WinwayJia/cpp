/*
 * 给定一个二叉树，在树的最后一行找到最左边的值。
 */
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

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        int findBottomLeftValue(TreeNode* root) {
            queue<pair<TreeNode*, int>> q;
            q.push(pair<TreeNode*, int>(root, 1));
            int maxLevel = 0;
            int result = root->val;

            while (!q.empty()) {
                auto n = q.front();
                q.pop();

                if (n.second > maxLevel) {
                    result = n.first->val;
                    maxLevel = n.second;
                }

                if (n.first->left) {
                    q.push(pair<TreeNode*, int>(n.first->left, n.second+1));
                }
                if (n.first->right) {
                    q.push(pair<TreeNode*, int>(n.first->right, n.second+1));
                }
            }
            return result;
        }
};

int main(int argc, const char** argv) {
    Solution s;
}
