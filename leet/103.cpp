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
#include <iterator>
#include <algorithm>

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
        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            if (nullptr == root) {
                return ans;
            }

            list<TreeNode*> l;
            l.push_front(root);

            vector<int> tmp;
            list<TreeNode*> level;
            int direction = -1;
            while(!l.empty()) {
                tmp.clear();
                int size = l.size();
                while (size --) {
                    auto& i = l.front();
                    tmp.push_back(i->val);
                    if (i->left) {
                        l.push_back(i->left);
                    }
                    if (i->right) {
                        l.push_back(i->right);
                    }
                    l.pop_front();
                }
                if (-1 == direction) {
                    direction = 1;
                } else {
                    std::reverse(tmp.begin(), tmp.end());
                    direction = -1;
                }
                ans.push_back(tmp);
            }

            return ans;
        }

        vector<vector<int>> levelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            if (nullptr == root) {
                return ans;
            }
            queue<pair<TreeNode*, int>> q;
            q.push(pair<TreeNode*, int>(root, 1));

            int level = 1;

            vector<int> tmp;
            while (!q.empty()) {
                auto& x = q.front();
                q.pop();
                if (x.second == level) {
                    tmp.push_back(x.first->val);
                } else {
                    level += 1;
                    ans.push_back(tmp);
                    tmp.clear();
                    tmp.push_back(x.first->val);
                }
                if (x.first->left) {
                    q.push(pair<TreeNode*, int>(x.first->left, level+1));
                }
                if (x.first->right) {
                    q.push(pair<TreeNode*, int>(x.first->right, level+1));
                }
            }
            if (!tmp.empty()) {
                ans.push_back(tmp);
            }
            for (int i=1; i<ans.size(); i+=2) {
                std::reverse(ans[i].begin(), ans[i].end());
            }

            return ans;
        }
};

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    list<TreeNode *> cache(1, root);
    int one = 1, two = 0;
    result.emplace_back();
    while (!cache.empty()) {
        if (!one) {
            result.emplace_back();
            one = two;
            two = 0;
        }
        TreeNode *top = cache.front();
        result.back().push_back(top->val);
        cache.pop_front();
        one--;
        if (top->left) {
            cache.push_back(top->left);
            two++;
        }
        if (top->right) {
            cache.push_back(top->right);
            two++;
        }
    }
    int len = result.size();
    for (int i = 1; i < len; i += 2)
        reverse(result[i].begin(), result[i].end());
    return result;
}



#include <benchmark/benchmark.h>
TreeNode* CreateTree() {
    TreeNode *n15 = new TreeNode(15);
    TreeNode *n2 = new TreeNode(2);
    TreeNode *n20 = new TreeNode(20);
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n3 = new TreeNode(3);
    TreeNode *n17 = new TreeNode(17);
    TreeNode *n22 = new TreeNode(22);

    n15->left = n2;
    n15->right = n20;

    n2->left = n1;
    n2->right = n3;

    n20->left = n17;
    n20->right = n22;

    return n15;
}
TreeNode* root = CreateTree();

static void BM_best(benchmark::State& state) {
    for (auto _ : state)
        zigzagLevelOrder(root);
}

static void BM_mine(benchmark::State& state) {
    Solution s;
    for (auto _ : state) 
        s.zigzagLevelOrder(root);

}

// Register the function as a benchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN(); //程序入口
