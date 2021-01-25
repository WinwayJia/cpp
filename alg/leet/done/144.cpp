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
#include <stack>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

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
        vector<int> preorderTraversal(TreeNode* root) {
            vector<int> ans;
            if (nullptr == root) {
                return ans;
            }

            deque<pair<TreeNode*, int>> dq;
            dq.push_front(make_pair(root, 0)); // 0 - pass by 1 - visit

            while (!dq.empty()) {
                auto it = dq.front();
                dq.pop_front();

                if (it.second == 1) {
                    ans.push_back(it.first->val);
                } else {
                    if (nullptr != it.first->right) dq.push_front(make_pair(it.first->right, 0));
                    dq.push_front(make_pair(it.first, 1));
                    if (nullptr != it.first->left) dq.push_front(make_pair(it.first->left, 0));
                }
            }

            return ans;
        }
};

TEST(TestMine, HandleNoraml) {
    Solution s;
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;

    vector<int> ans = {1, 2, 4, 5, 3, 6};
    vector<int> ret = s.preorderTraversal(node1);
    EXPECT_EQ(ans, ret);
    for (auto x : ret) {
        cout << " " << x;
    }
    cout << endl;
}

#ifdef _TEST_
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
//Register the function as abenchmark
BENCHMARK_MAIN();   //程序入口
#endif

