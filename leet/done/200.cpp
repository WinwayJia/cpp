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

class Solution
{
    struct Node
    {
        int h;
        int v;
        Node(int h_, int v_) : h(h_), v(v_) {}
        bool operator==(Node &n) const
        {
            return n.h == h && n.v == v;
        }

        bool operator<(const Node &n) const
        {
            return n.h > h || (n.h == h && n.v > v);
        }
    };

public:
    int expand(int h, int v, const vector<vector<char>> &grid, set<Node> &visited)
    {
        int ans = 0;
        if (grid[h][v] == '0')
        {
            return ans;
        }

        auto it = visited.find(Node(h, v));
        if (it != visited.end())
        {
            return ans;
        }

        queue<Node> q;
        q.emplace(h, v);
        while (!q.empty())
        {
            auto n = q.front();
            q.pop();

            auto it = visited.find(Node(n.h, n.v));
            if (it != visited.end())
            {
                continue;
            }
            visited.emplace(n.h, n.v);
            ans = 1;
            // up
            if (n.h > 0 && '1' == grid[n.h - 1][n.v])
            {
                q.emplace(n.h - 1, n.v);
            }
            // down
            if (n.h < grid.size() - 1 && '1' == grid[n.h + 1][n.v])
            {
                q.emplace(n.h + 1, n.v);
            }
            // left
            if (n.v > 0 && '1' == grid[n.h][n.v - 1])
            {
                q.emplace(n.h, n.v - 1);
            }
            // right
            if (n.v < grid[n.h].size() - 1 && '1' == grid[n.h][n.v + 1])
            {
                q.emplace(n.h, n.v + 1);
            }
        }
        return ans;
    }
    int numIslands(vector<vector<char>> &grid)
    {
        set<Node> visited;
        int ans = 0;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                ans += expand(i, j, grid, visited);
            }
        }
        return ans;
    }
};

TEST(TestSolution, HandlerNormal)
{
    Solution s;
    {
        vector<vector<char>> grid = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'},
        };
        cout << s.numIslands(grid) << endl;
    }
    {
        vector<vector<char>> grid = {{'1'}, {'1'}};
        cout << s.numIslands(grid) << endl;
    }
    {
        vector<vector<char>> grid = {{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}};
        cout << s.numIslands(grid) << endl;
    }
}

static void BM_best(benchmark::State &state)
{
}

static void BM_mine(benchmark::State &state)
{
}

#ifdef _TEST_
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
//Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
#endif
