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

class Solution {
    public:
        string convert(string s, int numRows) {
            if (1 == numRows) {
                return s;
            }
            int minRow = std::min(numRows, int(s.size()));
            bool down = false;
            int r = 0;
            std::vector<std::string> rows(minRow);

            for (auto& c : s) {
                rows[r] += c;
                if (0 == r || r == minRow-1) {
                    down = !down;
                }
                r += down ? 1 : -1;
            }

            std::string ans;
            for (auto& row : rows) {
                ans += row;
            }

            return ans;
        }
};

TEST(TestSolution, HandlerNormal) {
    std::string str = "LEETCODEISHIRING";
    Solution s;
    auto ans = s.convert(str, 3);

    cout << ans << endl;
    EXPECT_EQ("LCIRETOESIIGEDHN", ans);
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
