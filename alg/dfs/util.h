#include <vector>

struct Node {
    char val_;
    std::vector<Node*> links_;

    Node(char val) : val_(val) {}
    Node(int val, std::vector<Node*>& links) : val_(val), links_(links) {}
};