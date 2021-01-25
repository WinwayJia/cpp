#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>

using namespace std;


class Solution {
    public:
        char findTheDifference(string s, string t) {
            int arr[26] = {0};
            for (auto &c : s) {
                arr[c - 'a'] += 1; 
            }
            for (auto &c : t) {
                if (arr[c - 'a'] == 0) {
                    return c;
                }
                arr[c- 'a'] -= 1;
            }
        }

        char findTheDifference2(string s, string t) {
            int i = 0;
            for(auto &j : s) {
                i ^= j;
            }
            for(auto &j : t) {
                i ^= j;
            }
            return i;
        }

};

int main(int argc, const char** argv) {
    Solution s;
    cout << s.findTheDifference2("abcd", "abcde") << endl;
    cout << s.findTheDifference2("", "a") << endl;
    cout << s.findTheDifference2("aa", "aaa") << endl;
}
