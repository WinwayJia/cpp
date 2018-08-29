/*
 * 给定两个二进制字符串，返回他们的和（用二进制表示）。
 * 输入为非空字符串且只包含数字 1 和 0。
 *
 * 示例 1:
 * 输入: a = "11", b = "1"
 * 输出: "100"
 *
 * 示例 2:
 * 输入: a = "1010", b = "1011"
 * 输出: "10101"
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
        string addBinary(string a, string b) {
            string result;
            char flag = 0;
            char tmp;
            for (int i=a.size()-1, j=b.size()-1; i>=0 || j>=0; i--, j--) {
                tmp = (i<0?'0':a[i]) + (j<0?'0':b[j]) - '0' - '0' + flag;
                if (tmp >= 2) {
                    flag = 1;
                    result.insert(result.begin(), tmp - 2 + '0');
                } else {
                    result.insert(result.begin(), tmp + '0');
                    flag = 0;
                }
            }
            if (flag) {
                result.insert(result.begin(), char(flag + '0'));
            }
            return result;
        }
};

int main(int argc, const char** argv) {
    Solution s;

//    cout << s.addBinary("1010", "1011") << endl;
    cout << s.addBinary("1", "11") << endl;
}
