/*
 * 给定一个字符串 S 和一个字符 C。返回一个代表字符串 S 中每个字符到字符串 S 中的字符 C 的最短距离的数组。
 * 示例 1:
 * 输入: S = "loveleetcode", C = 'e'
 * 输出: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 * 说明:
 * 字符串 S 的长度范围为 [1, 10000]。
 * C 是一个单字符，且保证是字符串 S 里的字符。
 * S 和 C 中的所有字母均为小写字母。
 */
#include <stdio.h>
#include <stdint.h>
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
        vector<int> shortestToChar(string S, char C) {
            vector<int> result(S.size(), S.size()-1);
            int prev = -1;
            for (int i=0; i<S.size(); i++) {
                if (S[i] == C) {
                    result[i] = 0;
                    for (int j=i-1; j>=0; j--) {
                        if (result[j] > i - j) {
                            result[j] = i - j;
                        } else {
                            break;
                        }
                    }
                    prev = i;
                } else {
                    if (prev != -1) {
                        result[i] = i - prev;
                    }
                }
            }

            return result;
        }

        vector<int> best(string S, char C) {
            int sz = S.size();
            vector<int> result(sz);
            if (S[0] != C) {
                result[0]=999;
            }
            for(int i=1; i<sz; ++i){
                if(S[i] != C){
                    result[i] = result[i-1] + 1;
                }
            }
            for (int i=sz-2; i>=0; --i) {
                if(result[i] > result[i+1]) {
                    result[i] = result[i+1] + 1;
                }
            }
            return result;
        }
};

int main(int argc, const char** argv) {
    Solution s;

    //auto result = s.shortestToChar("loveleetcode", 'e');
    auto result = s.best("loveleetcode", 'e');
    for (auto i:result) {
        cout << i << " ";
    }
    cout << endl;
}
