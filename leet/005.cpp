/*
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为1000。
 *
 * 示例 1：
 * 输入: "babad"
 * 输出: "bab"
 * 注意: "aba"也是一个有效答案。
 *
 * 示例 2：
 * 输入: "cbbd"
 * 输出: "bb"
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
        string longestPalindrome(string s) {
            if (s.empty()) {
                return "";
            } 
            if (s.size() == 1) {
                return s;
            }
            if (s.size() ==2 && s[0] == s[1]) {
                return s;
            }
            int b;
            int e;
            int pos = 0;
            int len = 1;
            for (int i=1; i<s.size()-1; i++) {
                b = i-1;
                e = i+1; 
                if (s[i] == s[e]) {
                    pos = i;
                    len = 2;
                }
                if (s[i] == s[b]) {
                    pos = b;
                    len = 2;
                }
                while (s[b] == s[e]) {
                    b --;
                    e ++;
                    if (b < 0) {
                        break;
                    }
                    if (e >= s.size()+1) {
                        break;
                    }
                }
                
                if (e-b-1>len) {
                    pos = b+1;
                    len = e-b-1;
                }
            }
            return s.substr(pos, len);
        }
};

string longestPalindrome(string s) {
    string t = "$#";
    for(int i=0;i<s.size();i++){
        t+=s[i];
        t+="#";
    }
    vector<int>p(t.size(),0);
    int mx=0,id=0,resLen=0,resCenter=0;
    for(int i=1;i<t.size();i++){
        p[i]=mx>i?min(p[2*id-i],mx-i):1;
        while(t[i+p[i]]==t[i-p[i]]) ++p[i];
        if(mx<i+p[i]){
            mx=i+p[i];
            id=i;
        }
        if(resLen<p[i]){
            resLen=p[i];
            resCenter=i;
        }
    }
    string str=s.substr((resCenter-resLen)/2,resLen-1);
    return str;
}

int main(int argc, const char** argv) {
    Solution s;

    cout << s.longestPalindrome("bababddtatt") << endl;
    cout << s.longestPalindrome("babad") << endl;
    cout << s.longestPalindrome("bb") << endl;
}
