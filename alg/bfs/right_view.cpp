#include "util.h"
#include <queue>
#include <vector>

std::vector<int> rightView(TreeNode *root) {
    std::vector<int> ans;
    ans.reserve(32);

    if (root == nullptr) {
        return ans;
    }

    std::queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        auto size = q.size();

        for (int i = 0; i < size; i++) {
            auto node = q.front();
            q.pop();

            if (i == size - 1) {
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

void do_it(std::vector<int> &ans, TreeNode *root, int high) {
    if (root == nullptr) {
        return;
    }

    if (high >= ans.size()) {
        ans.resize(high + 1);
    }

    ans[high] = root->val;

    do_it(ans, root->left, high + 1);
    do_it(ans, root->right, high + 1);
}

std::vector<int> right_view_v2(TreeNode *root) {
    std::vector<int> ans;
    do_it(ans, root, 0);

    return ans;
}