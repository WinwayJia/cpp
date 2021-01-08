/*
 * 颠倒给定的 32 位无符号整数的二进制位。
 * 示例:
 * 输入: 43261596
 * 输出: 964176192
 * 解释: 43261596 的二进制表示形式为 00000010100101000001111010011100 ，
 *      返回 964176192，其二进制表示形式为 00111001011110000010100101000000 。
 *      进阶:
 * 如果多次调用这个函数，你将如何优化你的算法？
 */
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
        uint8_t reverse8(uint8_t x) {
            uint8_t bit0 = (x & 0x01);
            uint8_t bit1 = (x & 0x02)>>1;
            uint8_t bit2 = (x & 0x04)>>2;
            uint8_t bit3 = (x & 0x08)>>3;
            uint8_t bit4 = (x & 0x10)>>4;
            uint8_t bit5 = (x & 0x20)>>5;
            uint8_t bit6 = (x & 0x40)>>6;
            uint8_t bit7 = (x & 0x80)>>7;

            return (bit0 << 7) + (bit1 << 6) + (bit2 << 5) + (bit3 << 4) + 
                   (bit4 << 3) + (bit5 << 2) + (bit6 << 1) + bit7;

        }
        uint32_t reverseBits(uint32_t n) {
            uint8_t *slice = (uint8_t*)&n;
            uint8_t tmp;

            slice[0] = reverse8(slice[0]);
            slice[1] = reverse8(slice[1]);
            slice[2] = reverse8(slice[2]);
            slice[3] = reverse8(slice[3]);

            tmp = slice[3];
            slice[3] = slice[0];
            slice[0] = tmp;

            tmp = slice[2];
            slice[2] = slice[1];
            slice[1] = tmp;

            return *(uint32_t*)(slice);
        }
};

int main(int argc, const char** argv) {
    Solution s;
    cout << s.reverseBits(43261596) << endl;

    uint8_t c = 0x61;
    printf("%0x %0x\n", c, s.reverse8(c));
}
