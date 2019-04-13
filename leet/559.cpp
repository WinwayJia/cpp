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
        int maxDepth(Node* root) {
            int ans = 0;
            if (nullptr == root) {
                return ans;
            }

            ans = 1;
            queue<Node*> q;
            root->val = 1;
            q.push(root);

            while (!q.empty()) {
                auto n = q.front();
                q.pop();
                for (auto c : n->children) {
                    c->val = n->val + 1;
                    if (c->val > ans) {
                        ans = c->val;
                    }
                    q.push(c);
                }
            }
            return ans;
        }
};


int main(int argc, const char** argv) {
    Solution s;

    Node* n = new Node(44, vector<Node*>{});

    cout << s.maxDepth(n) << endl;
}
