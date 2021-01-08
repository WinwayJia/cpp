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
#include <queue>
#include <stack>
#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

using namespace std;

/*
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 */

class Solution {
    public:
        string intToRoman(int num) {
            vector<string> thousands = {"", "M", "MM", "MMM"};
            vector<string> hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
            vector<string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
            vector<string> sigs = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

            return thousands[num / 1000] + hundreds[num/100%10] + tens[num/10%10] + sigs[num%10];
        }
};


TEST(TestSolution, HandlerNormal) {
    {
        int num = 3898;
        Solution s;
        EXPECT_EQ(s.intToRoman(num), "MMMDCCCXCVIII");
    }
    {
        int num = 147;
        Solution s;
        EXPECT_EQ(s.intToRoman(num), "CXLVII");
    }
}

static void BM_best(benchmark::State& state) {
}

static void BM_mine(benchmark::State& state) {
}

#ifdef _TEST_
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
    //Register the function as abenchmark
    BENCHMARK(BM_mine); //用于注册测试函数
    BENCHMARK(BM_best); //用于注册测试函数
    BENCHMARK_MAIN();   //程序入口
#endif

