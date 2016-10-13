/*
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']'
 * , determine if the input string is valid. The brackets must close in the 
 * correct order, "()" and "()[]" are all valid but "(]" and "([)]" are not.
 */
#include <iostream>
#include <string>
#include "t_stack.cpp"
using namespace std;

class Solution {
    public:
        string left = "([{";
        string right = ")]}";
        bool isValid (string const& s) {
            CStack<char>  stack(64);
            for (auto c : s) {
                if (left.find(c) != string::npos) {
                    stack.push(c);
                } else if (right.find(c) != string::npos) {
                    if (stack.top() != left[right.find(c)]) {
                        return false;
                    } else {
                        stack.pop();
                    }
                }
            }
            return stack.empty();
        }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s expr\n", argv[0]);
        return 0;
    }
    Solution s;

    cout << s.isValid(argv[1]) << endl;
    return 0;
}
