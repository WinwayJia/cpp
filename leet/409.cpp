/*
 * 给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。
 *
 * 在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。
 *
 * 注意:
 * 假设字符串的长度不会超过 1010。
 *
 * 示例 1:
 * 输入: "abccccdd"
 * 输出: 7
 * 解释: 我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
 */
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    public:
        int longestPalindrome(string s) {
            unordered_map<char, int> stat;
            int result = 0;
            for (auto c : s) {
                auto ret = stat.insert(unordered_map<char, int>::value_type(c, 1));
                if (false == ret.second) {
                    result += 2;
                    stat.erase(ret.first);
                }
            }

            return result + (stat.size() > 0 ? 1 : 0);
        }
};

int main(int argc, const char** argv) {
    Solution s;
    cout << s.longestPalindrome("abccccdd") << endl;
    cout << s.longestPalindrome("a") << endl;
}
