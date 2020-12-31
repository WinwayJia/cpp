/**
  * Definition for a binary tree node.
  */
#include <queue>
#include "util.h"
#include "../sort/util.h"

    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        std::queue<TreeNode*> q;
        q.push(root);

        int ans = 0;
        while (!q.empty()) {
            ans ++;
            auto size = q.size();
            for (int i=0; i<size; i++) {
                auto node = q.front();
                q.pop();
                if (node->left == nullptr && node->right == nullptr) {
                    return ans;
                }

                if (node->left != nullptr) {
                    q.push(node->left);
                }

                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
        }

        return ans;
    }

int main() {
    auto one = new TreeNode(1);
    auto two = new TreeNode(2);
    auto three = new TreeNode(3);
    auto four = new TreeNode(4);
    auto five = new TreeNode(5);
    auto six = new TreeNode(6);
    auto seven = new TreeNode(7);

    one->left = two;
    one->right = three;
    two->left = four;
    three->left = five;
    three->right = six;
    four->right = seven;


    std::cout << "minDepth: " << minDepth(one) << std::endl;

    std::cout << rightView(one) << std::endl;

    return 0;
}