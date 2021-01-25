#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

struct Node {
    int val_;
    std::vector<Node*> nexts_;
    Node(int val) : val_(val) {}
};

void dfs(Node* n, std::set<int>& visted, std::stack<Node*>& st) {
    visted.insert(n->val_);
    for (auto i : n->nexts_) {
        if (visted.find(i->val_) == visted.end()) {
            dfs(i, visted, st);
        }
    }

    st.push(n);
}

std::vector<int> topo_sort(std::vector<Node*>& nodes) {
    std::set<int> visited;
    std::vector<int> ans;
    std::stack<Node*> st;

    for (auto& n : nodes) {
        if (visited.find(n->val_) == visited.end()) {
            dfs(n, visited, st);
        }
    }

    while (!st.empty()) {
        ans.push_back(st.top()->val_);
        st.pop();
    }

    return ans;
}

int main(int argc, char const* argv[]) {
    Node* one = new Node(1);
    Node* two = new Node(2);
    Node* three = new Node(3);
    Node* four = new Node(4);
    Node* five = new Node(5);
    Node* six = new Node(6);
    Node* seven = new Node(7);
    Node* nine = new Node(9);
    one->nexts_.push_back(three);
    one->nexts_.push_back(two);
    two->nexts_.push_back(four);
    two->nexts_.push_back(six);
    three->nexts_.push_back(five);
    four->nexts_.push_back(five);
    four->nexts_.push_back(six);
    five->nexts_.push_back(seven);
    six->nexts_.push_back(nine);
    seven->nexts_.push_back(nine);

    std::vector<Node*> nodes = {one, two, three, four, five, six, seven, nine};

    auto ans = topo_sort(nodes);

    for (auto x : ans) {
        std::cout << x << " ";
    }

    std::cout << std::endl;

    return 0;
}
