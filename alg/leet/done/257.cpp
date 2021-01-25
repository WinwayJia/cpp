/*
   给定一个二叉树，返回所有从根节点到叶子节点的路径。

   说明: 叶子节点是指没有子节点的节点。
   示例:
   输入:
   1
   / \
   2   3
   \
   5

   输出: ["1->2->5", "1->3"]

   解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3
   */
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        vector<string> binaryTreePaths(TreeNode* root) {
        }
        void recure(TreeNode* root, string& str, string& left, string& right) {
            if (root) {
                stringstream ss;
                ss << root->val;
            }
            if (root->left) {
               recure(root->left, str, )
            }
            if (root->right) {

            }
        }

};

int main(int argc, const char** argv) {
    Solution s;
}
