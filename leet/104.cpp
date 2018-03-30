/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Guid {

public:
    Guid(TreeNode* node, int op) : node_(node), op_(op){ 
    }
    TreeNode* node_;
    int op_; // 1 - visit 2 - 
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return right > left ? right + 1 : left + 1;
    }

    int maxDepth2(TreeNode* root) {

    }
};
