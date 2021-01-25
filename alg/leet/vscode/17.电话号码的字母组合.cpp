/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

#include "head.h"

// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<vector<char>> table = {
            {},
            {},
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'},
            {'j', 'k', 'l'},
            {'m', 'n', 'o'},
            {'p', 'q', 'r', 's'},
            {'t', 'u', 'v'},
            {'w', 'x', 'y', 'z'},
        };

        vector<string> ans;
        if (digits.empty()) {
            return ans;
        }

        std::function<void(string&, int)> fn = [&](string& item, int pos) {
            if (pos >= digits.size()) {
                ans.push_back(item);
                return;
            }

            auto& mapping = table[digits[pos] - '0'];
            for (int i = 0; i < mapping.size(); i++) {
                item.push_back(mapping[i]);
                fn(item, pos + 1);
                item.resize(item.size() - 1);
            }
        };

        string item;
        fn(item, 0);

        return ans;
    }
};
// @lc code=end

int main(int argc, char const* argv[]) {
    string digits = "23";

    Solution s;
    auto ans = s.letterCombinations(digits);

    for (auto& item : ans) {
        cout << item << " ";
    }

    cout << endl;
    return 0;
}
