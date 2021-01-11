#ifndef __BFS_UTIL_H__
#define __BFS_UTIL_H__

#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

std::vector<int> rightView(TreeNode* root);
std::vector<int> right_view_v2(TreeNode* root);

#endif // __BFS_UTIL_H__