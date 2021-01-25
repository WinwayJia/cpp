/*
 * 给定一个N叉树，返回其节点值的层序遍历。 (即从左到右，逐层遍历)。
 */
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

using namespace std;



// Definition for a Node.
class Node {
    public:
        int val = NULL;
        vector<Node*> children;

        Node() {}

        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
};

class Solution {
    public:
        vector<vector<int>> levelOrder(Node* root) {
            vector<vector<int>> ans;
            if (nullptr == root) {
                return ans;

            }

            queue<pair<Node*,int>> q;
            q.push(pair<Node*, int>(root, 0));

            while (!q.empty()) {
                auto n = q.front();
                q.pop();

                if (ans.size() < n.second+1) {
                    ans.push_back(vector<int>{});

                }
                ans[n.second].push_back(n.first->val);
                for (auto c : n.first->children) {
                    q.push(pair<Node*, int>(c, n.second+1));

                }

            }

            return ans;

        }

};
int main(int argc, const char** argv) {
    Solution s;

    Node* n6 = new Node(6, vector<Node*>{});
    Node* n3 = new Node(3, vector<Node*>{n6});

    Node* n0 = new Node(0, vector<Node*>{});
    Node* n5 = new Node(5, vector<Node*>{});
    Node* n10 = new Node(10, vector<Node*>{n5, n0});

    Node* n1 = new Node(1, vector<Node*>{n10, n3});

    auto ans = s.levelOrder(n1);

    return 0;
}
