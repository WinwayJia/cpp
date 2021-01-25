#include "util.h"
#include <functional>
#include <unordered_set>

Node* build_map() {
    Node* a = new Node('a');
    Node* b = new Node('b');
    Node* c = new Node('c');
    Node* d = new Node('d');
    Node* e = new Node('e');
    Node* f = new Node('f');

    a->links_.push_back(b);
    a->links_.push_back(d);
    b->links_.push_back(c);
    c->links_.push_back(f);
    d->links_.push_back(e);
    e->links_.push_back(b);

    return a;
}

std::vector<char> dfs(Node* root) {
    std::vector<char> path;
    std::unordered_set<char> visited;

    std::function<void(Node*)> fn = [&fn, &path, &visited](Node* root) {};
    return path;
}

int main(int argc, char const* argv[]) { return 0; }
