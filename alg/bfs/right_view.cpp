#include <queue>
#include <vector>
#include "util.h"

std::vector<int> rightView(TreeNode* root) {
    std::vector<int> ans;
    ans.reserve(32);

    if (root == nullptr) {
        return ans;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        auto size = q.size();

        for (int i=0; i<size; i++) {
            auto node = q.front();
            q.pop();

            if (i == size-1) {
                ans.push_back(node->val);
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