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


static void BM_best(benchmark::State& state) {
    Solution s;
    for (auto _ : state)
        s.restoreIpAddresses("25525511135");
}

TEST(TestisValidIPField, HandlerNormal) {
    Solution s;
    EXPECT_EQ(true, s.isValidIPField("255"));
}

TEST(TestMine, HandleNoraml) {
    Solution s;
    std::vector<std::string> ans = {"255.255.11.135", "255.255.111.35"};
    EXPECT_EQ(ans, s.restoreIpAddresses("25525511135"));
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

