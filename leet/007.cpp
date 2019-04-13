/*
 * 给定一个 32 位有符号整数，将整数中的数字进行反转。
 *
 * 示例 1:
 * 输入: 123
 * 输出: 321
 *
 * 示例 2:
 * 输入: -123
 * 输出: -321
 *
 * 示例 3:
 * 输入: 120
 * 输出: 21
 * 注意:  假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31,  2^31 − 1]。根据这个假设，如果反转后的整数溢出，则返回 0。
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
        int reverse(int x) {
            int64_t result = 0;
            while (x) {
                result += (x % 10);
                result = result * 10;
                x = x / 10;
            }
            result = result / 10;
            int min = 0x80000000;
            int max = 0x7FFFFFFF;
            if (result > max || result < min) {
                return 0;
            } 
            return int(result);
        }

};

int main(int argc, const char** argv) {
    Solution s;

//    cout << s.reverse(123) << endl;
    cout << s.reverse(-1223) << endl;
    cout << s.reverse(2147483648) << endl;
}
