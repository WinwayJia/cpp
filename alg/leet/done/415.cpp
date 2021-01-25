#include <vector>
#include <string>
#include <iostream>

using namespace std;
























class Solution {
    public:
        string addStrings(string num1, string num2) {
            string result;
            size_t size1 = num1.size();
            size_t size2 = num2.size();
            char flag = 0;
            char tmp;
            int a, b;
            for (size_t i=size1, j=size2; i>0 || j>0; ) {
                a = i > 0 ? num1[--i] - '0' : 0;
                b = j > 0 ? num2[--j] - '0' : 0;
                tmp = a + b + flag;
                if (tmp >= 10) {
                    flag = 1;
                    tmp -= 10;
                } else {
                    flag = 0;
                }
                result = string(1, '0' + tmp) + result;
            }
            if (flag) {
                result = string(1, '0' + flag) + result;
            }

            return result;
        }

};

int main(int argc, const char** argv) {
    Solution s;

//    cout << s.addStrings("123", "123") << endl;
//    cout << s.addStrings("123", "923") << endl;
    cout << s.addStrings("23", "977") << endl;
}
