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

int getCount(int n) {
    int ans = 0;
    while (n) {
        n = n & (n-1);
        ans ++;
    }
    return ans;
}

vector<int> countBits(int num) {
    vector<int> ans;
    for (int i=0; i<=num; i++) {
        ans.push_back(getCount(i));
    }

    return ans;
}

vector<int> countBitsDP(int num) {
    vector<int> res;
    res.push_back(0);

    for (int i = 1; i <= num; ++ i) {
        if (i & 0x01) {
            res.push_back(res[i>>1] + 1);
        } else {
            res.push_back(res[i>>1]);
        }
    }
    return res;
}


static void BM_CountBits(benchmark::State& state) {
    for (auto _ : state)
        countBits(10);
}

static void BM_CountBitsDP(benchmark::State& state) {
    for (auto _ : state)
        countBitsDP(10);
}


BENCHMARK(BM_CountBits); 
BENCHMARK(BM_CountBitsDP); 
BENCHMARK_MAIN();
