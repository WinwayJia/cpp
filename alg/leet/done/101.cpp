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
        bool isSymmetric(TreeNode* root) {
            if (nullptr == root) {
                return true;
            }
            return isSymmetric(root->left, root->right);
        }

        bool isSymmetric(TreeNode* left, TreeNode* right) {
            if (nullptr == left && nullptr == right) {
                return true;
            }

            if ((nullptr != left && nullptr == right) || (nullptr == left && nullptr != right)) {
                return false;
            }

            if (left->val != right->val) {
                return false;
            }

            return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
        } 
};

namespace iteration {
    class Solution {
        public:
            bool isSymmetric(TreeNode* root) {
                if (nullptr == root) {
                    return true;
                }
                queue<TreeNode*> q1;
                queue<TreeNode*> q2;
                q1.push(root->left);
                q2.push(root->right);

                while (!q1.empty() && q2.empty()) {
                    auto left = q1.front();
                    q1.pop();
                    auto right = q2.front();
                    q2.pop();

                    if (nullptr == left && nullptr == right) {
                        continue;
                    }
                    if (nullptr == left || nullptr == right) {
                        return false;
                    }
                    
                    if (left->val != right->val) {
                        return false;
                    }

                    q1.push(left->left);
                    q1.push(left->right);
                    q2.push(right->right);
                    q2.push(right->left);
                }

                return true;
            }
    }


    TEST(TestSolution, HandlerNormal) {
        TreeNode* node1 = 
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

