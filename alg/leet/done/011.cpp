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

/*
 * Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). 
 * n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
 * Find two lines, which together with x-axis forms a container, such that the container contains the most water.
 *
 * Note: You may not slant the container and n is at least 2.
 * Example:
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 */

class Solution {
    public:
        // O(n^2)
        int maxArea(vector<int>& height) {
            int ans = 0;
            for (int i=0; i<height.size()-1; i++) {
                for (int j=i+1; j<height.size(); j++) {
                    ans = std::max(ans, std::min(height[i], height[j])*(j-i));
                }
            }

            return ans;
        }

        // O(n)
        int maxAreaBest(vector<int>& height) {
            int i = 0; 
            int j = height.size() - 1;
            int ans = 0;

            while (i < j) {
                ans = std::max(ans, std::min(height[i], height[j])*(j-i));
                height[i] > height[j] ? j-- : i++;
            }
            return ans;
        }
};


Solution s;
std::vector<int> input = {1,8,6,2,5,4,8,3,7};
static void BM_best(benchmark::State& state) {
        std::cout << s.maxAreaBest(input) << std::endl;
    for (auto _:state)
        s.maxAreaBest(input);
}

static void BM_mine(benchmark::State& state) {
        std::cout << s.maxArea(input) << std::endl;
    for (auto _:state)
        s.maxArea(input);
}

//Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
