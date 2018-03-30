#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>

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
        int height(TreeNode* root) {
            if (!root) {
                return 0;
            }
            int left = height(root->left);
            int right = height(root->right);
            return left > right ? left + 1 : right + 1;
        }

        bool isBalanced(TreeNode* root) {
            if (!root) {
                return true;
            }
            int left = height(root->left);
            int right = height(root->right);

            bool result = left == right || (left + 1) == right || (right + 1)== left;
            return result && isBalanced(root->left) && isBalanced(root->right);
        }
};


int main(int argc, const char** argv) {
    Solution s;
}
