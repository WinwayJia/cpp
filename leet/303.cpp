/*
 * 给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。
 *
 * 示例：
 * 给定 nums = [-2, 0, 3, -5, 2, -1]，求和函数为 sumRange()
 *
 * sumRange(0, 2) -> 1
 * sumRange(2, 5) -> -1
 * sumRange(0, 5) -> -3
 *
 * 说明:
 * 你可以假设数组不可变。
 * 会多次调用 sumRange 方法。
 */
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

using namespace std;


class NumArray {
    public:
        NumArray(vector<int> nums) {
            sum_.push_back(0);
            for (int num :nums) {
                sum_.push_back(sum_.back() + num);
            }
        }

        int sumRange(int i, int j) {
            return sum_[j+1] - sum_[i+1];
        }

        vector<int> sum_;

};


int main(int argc, const char** argv) {
    NumArray s({-2,0,3,-5,2,-1});

    cout << s.sumRange(0, 2) << endl;
    return 0;
}
