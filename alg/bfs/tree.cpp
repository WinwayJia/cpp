/**
 * Definition for a binary tree node.
 */
#include "../sort/util.h"
#include "util.h"
#include <functional>
#include <queue>

int minDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    std::queue<TreeNode*> q;
    q.push(root);

    int ans = 0;
    while (!q.empty()) {
        ans++;
        auto size = q.size();
        for (int i = 0; i < size; i++) {
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

std::vector<int> pre_order(TreeNode* root) {
    std::vector<int> ans;
    std::function<void(TreeNode*, std::vector<int>&)> fn = [&fn](TreeNode* root,
                                                                 std::vector<int>& vec) {
        if (root == nullptr) {
            return;
        }

        vec.push_back(root->val);
        fn(root->left, vec);
        fn(root->right, vec);
    };

    fn(root, ans);

    return ans;
}

std::vector<int> mid_order(TreeNode* root) {
    std::vector<int> ans;

    std::function<void(TreeNode*, std::vector<int>&)> fn = [&fn](TreeNode* root,
                                                                 std::vector<int>& vec) {
        if (root == nullptr) {
            return;
        }

        fn(root->left, vec);
        vec.push_back(root->val);
        fn(root->right, vec);
    };

    fn(root, ans);

    return ans;
}

std::vector<int> post_order(TreeNode* root) {
    std::vector<int> ans;

    std::function<void(TreeNode*, std::vector<int>&)> fn = [&fn](TreeNode* root,
                                                                 std::vector<int>& vec) {
        if (root == nullptr) {
            return;
        }

        fn(root->left, vec);
        fn(root->right, vec);
        vec.push_back(root->val);
    };

    fn(root, ans);

    return ans;
}
struct Elem {
    enum Type {
        ByPass = 1,
        Visit = 2,
    };
    TreeNode* node_;
    Type type_; // 1 - bypass 2 - visit

    Elem(TreeNode* node, Type type) : node_(node), type_(type) {}
};

std::vector<int> traverse(TreeNode* root, const char order[3] = "rlc") {
    std::vector<int> ans;
    if (nullptr == root) {
        return ans;
    }

    std::deque<Elem> q;
    q.push_front(Elem(root, Elem::ByPass));

    while (!q.empty()) {
        auto front = q.front();
        q.pop_front();
        if (front.type_ == Elem::Visit) {
            ans.push_back(front.node_->val);
            continue;
        }

        for (int i = 0; i < 3; i++) {
            switch (order[i]) {
            case 'r':
                if (front.node_->right != nullptr) {
                    q.push_front(Elem(front.node_->right, Elem::ByPass));
                }
                break;
            case 'l':
                if (front.node_->left != nullptr) {
                    q.push_front(Elem(front.node_->left, Elem::ByPass));
                }
                break;
            case 'c':
                front.type_ = Elem::Visit;
                q.push_front(front);
            default:
                // print unknown order error
                break;
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

    std::cout << right_view_v2(one) << std::endl;

    std::cout << pre_order(one) << std::endl;
    std::cout << traverse(one) << std::endl;

    std::cout << mid_order(one) << std::endl;
    std::cout << traverse(one, "rcl") << std::endl;

    std::cout << post_order(one) << std::endl;
    std::cout << traverse(one, "crl") << std::endl;

    return 0;
}