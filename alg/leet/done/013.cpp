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
            vector<string> hundreds = {"", "C", "CC", "CCC", "CM", "D", "DC", "DCC", "DCCC", "CM"};
            vector<string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
            vector<string> sigs = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

            return thousands[num / 1000] + hundreds[num/100%10] + tens[num/10%10] + sigs[num%10];
        }

        int romanToInt(string s) {
            int ans = 0;
            if (s.empty()) {
                return ans;
            }
            vector<string> thousands = {"", "M", "MM", "MMM"};
            vector<string> hundreds = {"", "C", "CC", "CCC", "CM", "D", "DC", "DCC", "DCCC", "CM"};
            vector<string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
            vector<string> sigs = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

            unordered_map<string, int> mappings;
            for (int i=1; i<thousands.size(); i++) {
                mappings.emplace(thousands[i], i*1000);
            }
            for (int i=1; i<hundreds.size(); i++) {
                mappings.emplace(hundreds[i], i*100);
            }
            for (int i=1; i<tens.size(); i++) {
                mappings.emplace(tens[i], i*10);
            }
            for (int i=1; i<sigs.size(); i++) {
                mappings.emplace(sigs[i], i);
            }

            for (int i=0; i<s.size(); i++) {
                int j = i + 1;
                for (; j<s.size(); j++) {
                    auto it = mappings.find(s.substr(i, j-i));
                    if (it == mappings.end()) {
                        break;
                    }
                }
                auto it = mappings.find(s.substr(i, j-i));
                ans += it->second;
                i = j;
            }
            return ans;
        }
};


TEST(TestSolution, HandlerNormal) {
    {
        int num = 3898;
        string roman = "MMMDCCCXCVIII";
        Solution s;
        EXPECT_EQ(s.intToRoman(num), roman);
        EXPECT_EQ(s.romanToInt(roman), num);
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

