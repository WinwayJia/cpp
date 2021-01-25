#include <functional>
#include <iostream>
#include <stack>

struct Node {
    int val;
    Node* next;

    Node(int v) : val(v), next(nullptr) {}
    static void Print(Node* root) {
        while (root != nullptr) {
            std::cout << root->val << " -> ";
            root = root->next;
        }

        std::cout << "nullptr" << std::endl;
    }
};

Node* add_two_numbers(Node* left, Node* right) {
    if (nullptr == left) {
        return right;
    }

    if (nullptr == right) {
        return left;
    }

    std::stack<Node*> l;
    while (left != nullptr) {
        l.push(left);
        left = left->next;
    }

    std::stack<Node*> r;
    while (right != nullptr) {
        r.push(right);
        right = right->next;
    }

    std::stack<Node*> result;
    int flag = 0;
    while (!l.empty() && !r.empty()) {
        auto x = l.top();
        l.pop();
        auto y = r.top();
        r.pop();

        flag = x->val + y->val + flag;
        if (flag >= 10) {
            x->val = flag - 10;
            flag = 1;
        } else {
            x->val = flag;
            flag = 0;
        }

        result.push(x);
    }

    std::function<void(std::stack<Node*>&)> deal = [&result](std::stack<Node*>& st) {
        while (!st.empty()) {
            auto x = st.top();

            int flag = x->val + flag;
            if (flag >= 10) {
                x->val = flag - 10;
                flag = 1;
            } else {
                flag = 0;
            }
            st.pop();
            result.push(x);
        }
    };

    deal(l);
    deal(r);

    Node* ans = nullptr;
    if (flag) {
        auto x = new Node(1);
        ans = x;
    }

    if (ans == nullptr) {
        ans = result.top();
        result.pop();
    }

    Node* tmp = ans;
    while (!result.empty()) {
        tmp->next = result.top();
        result.pop();
        tmp = tmp->next;
    }

    return ans;
}

int main(int argc, char const* argv[]) {
    Node* two = new Node(5);
    Node* four = new Node(4);
    Node* three = new Node(3);
    two->next = four;
    four->next = three;

    Node* five = new Node(5);
    Node* six = new Node(6);
    Node* seven = new Node(7);
    five->next = six;
    six->next = seven;
    // (2->4->3) + (5->6->7)

    Node::Print(two);
    Node::Print(five);
    auto ans = add_two_numbers(two, five);
    Node::Print(ans);

    return 0;
}
