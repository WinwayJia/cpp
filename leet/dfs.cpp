#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    Node(char v) : val(v) {}

    char val;
    vector<Node*> adj;
};

unordered_set<char> visited;

void dfs(Node* n) {
    if (visited.find(n->val) != visited.end()) {
        return;
    }

    cout << n->val << " ";
    visited.insert(n->val);

    for (auto x : n->adj) {
        dfs(x);
    }

    return;
}

void bfs(Node* n) {
    unordered_set<char> visited;
    queue<Node*> q;
    q.push(n);
    visited.insert(n->val);

    while (!q.empty()) {
        Node* t = q.front();
        q.pop();
        cout << t->val << " ";
        for (auto x : t->adj) {
            if (visited.find(x->val) == visited.end()) {
                q.push(x);
                visited.insert(x->val);
            }
        }
    }
    return ;
}

int main() {
    Node *a = new Node('a');
    Node *b = new Node('b');
    Node *c = new Node('c');
    Node *d = new Node('d');
    Node *e = new Node('e');

    a->adj.push_back(b);
    a->adj.push_back(c);

    b->adj.push_back(d);

    c->adj.push_back(b);
    c->adj.push_back(e);

    e->adj.push_back(d);

    dfs(a);
    cout << endl;
    bfs(a);
    cout << endl;
}
