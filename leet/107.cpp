#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

/**
 *  Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        void recure(TreeNode* root, int level, vector<vector<int>> &result) {
            if (root == nullptr) {
                return ;
            }
            if (result.capacity() < level+1) {
                result.reserve(level+1);
                result.push_back(vector<int>());
            } 
            result[level].push_back(root->val);
            if (root->left) {
                recure(root->left, level+1, result);
            }
            if (root->right) {
                recure(root->right, level+1, result);
            }

        }
        vector<vector<int>> levelOrderBottom(TreeNode* root) {
            vector<vector<int>> result;
            recure(root, 0, result);
            return vector<vector<int>>(result.rbegin(), result.rend());
        }

};

int main(int argc, const char** argv) {
    Solution s;
    TreeNode root(1);
    TreeNode left(2);
    TreeNode right(3);
    TreeNode lr(4);
    root.left = &left;
    root.right = &right;
    root.left->right = &lr;

    auto result = s.levelOrder(&root);

    vector<int> vec;
    vec.push_back(10);
    vec.push_back(10);
    vec.push_back(10);


}
