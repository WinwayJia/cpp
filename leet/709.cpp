/*
   实现函数 ToLowerCase()，该函数接收一个字符串参数 str，并将该字符串中的大写字母转换成小写字母，之后返回新的字符串。

   示例 1：
   输入: "Hello"
   输出: "hello"

   示例 2：
   输入: "here"
   输出: "here"

   示例 3：
   输入: "LOVELY"
   输出: "lovely"
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
        string toLowerCase(string str) {
            string result;
            for (auto c : str) {
                if (c >= 'A' && c <= 'Z') {
                    result.push_back(c+32);
                } else {
                    result.push_back(c);
                }
            }
            return result;
        }

};

int main(int argc, const char** argv) {
    Solution s;
    cout << s.toLowerCase("LOVELY") << endl;
    cout << s.toLowerCase("Hello") << endl;
}
