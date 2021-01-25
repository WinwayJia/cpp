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
 * Given a string containing only digits, restore it by returning all possible valid IP address combinations.
 *
 * Example:
 *
 * Input: "25525511135"
 * Output: ["255.255.11.135", "255.255.111.35"]
 */

class Solution {
    public:
        vector<string> restoreIpAddresses(string s) {
            std::vector<std::string> ans;
            size_t size = s.size();
            for (int i=0; i<size-2 && i<3; i++) {
                for (int j=i+1; i<size-1 && j<4+i; j++) {
                    for (int k=j+1; k<size && k<4+j; k++) {
                        std::string f1 = s.substr(0, i+1);
                        std::string f2 = s.substr(i+1, j-i);
                        std::string f3 = s.substr(j+1, k-j);
                        std::string f4 = s.substr(k+1);
                        std::cout << f1 << " " << f2 << " " << f3 << " " << f4 << std::endl;
                        if (isValidIPField(f1) && isValidIPField(f2) && isValidIPField(f3) && isValidIPField(f4)) {
                            ans.push_back(f1+"."+f2+"."+f3+"."+f4);
                        }
                    }
                }
            }
            return ans;
        }

        bool isValidIPField(const std::string& str) {
            size_t size = str.size();
            if (0 == size || 3 < size) {
                return false;
            }
            if (size > 1 && '0' == str[0]) {
                return false;
            }
            if (std::stoi(str) > 255) {
                return false;
            }

            return true;
        }
};


static void BM_best(benchmark::State& state) {
    Solution s;
    for (auto _ : state)
        s.restoreIpAddresses("25525511135");
}

TEST(TestisValidIPField, HandlerNormal) {
    Solution s;
    EXPECT_EQ(true, s.isValidIPField("255"));
}

TEST(TestisValidIPField, HandlerZero) {
    Solution s;
    EXPECT_EQ(true, s.isValidIPField("0"));
}

TEST(TestMine, HandleNoraml) {
    Solution s;
    std::vector<std::string> ans = {"255.255.11.135", "255.255.111.35"};
    EXPECT_EQ(ans, s.restoreIpAddresses("25525511135"));
}

TEST(TestMine, HandlerFourZero) {
    Solution s;
    std::vector<std::string> ans = {"0.0.0.0"};
    EXPECT_EQ(ans, s.restoreIpAddresses("0000"));
}

static void BM_mine(benchmark::State& state) {
    Solution s;
    for (auto _ : state)
        s.restoreIpAddresses("25525511135");
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
