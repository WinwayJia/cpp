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

using namespace std;

static void BM_best(benchmark::State& state) {
    for (auto_:state)
        zigzagLevelOrder(root);
}

static void BM_mine(benchmark::State& state) {
    Solution s;
    for (auto _ : state)
        s.zigzagLevelOrder(root);
}

//Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
