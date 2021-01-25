/*
 * 给定一个N叉树，返回其节点值的后序遍历。
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
#include <stack>

using namespace std;

class Node {
    public:
        int val;
        vector<Node*> children;

        Node() {}

        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
};

class Solution {
    public:
        vector<int> postorder(Node* root) {
            vector<int> ans;
            if (nullptr == root) {
                return ans;
            }
            stack<pair<Node*, int>> s;
            s.push(pair<Node*, int>(root, 0));
            while (!s.empty()) {
                auto& n = s.top();
                if (n.first->children.empty() || n.second == 1) {
                    ans.push_back(n.first->val);
                    s.pop();
                } else {
                    n.second = 1;
                    for (auto it = n.first->children.rbegin(); it != n.first->children.rend(); it++) {
                        s.push(pair<Node*, int>(*it, 0));
                    }
                }
            }
            return ans;
        }
};


int main(int argc, const char** argv) {
    Solution s;
    Node* n5 = new Node(5, {});
    Node* n6 = new Node(6, {});

    Node* n3 = new Node(1, {n5, n6});
    Node* n2 = new Node(1, {});
    Node* n4 = new Node(1, {});
    Node* n1 = new Node(1, {n3, n2, n4});

    auto ans = s.postorder(n1);

    return 0;

}
