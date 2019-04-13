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
        bool isNear(const string& a, const string& b) {
            // assume a length eques b
            int diff = 0;
            for (int i=0; i<a.size(); i++) {
                if (a[i] != b[i]) {
                    diff ++;
                }
                if (diff >= 2) {
                    break;
                }
            }

            return diff == 1;
        }

        int bfs(int b, int e, const vector<vector<int>>& route) {
            std::queue<std::pair<int, int>> q;
            q.push(make_pair(b, 1));
            std::set<int> reached;

            int ans = -1;
            while (!q.empty()) {
                auto& x = q.front();
                q.pop();
                reached.insert(x.first);
                if (x.first == e) {
                    ans = x.second;
                }

                for (auto n : route[x.first]) {
                    auto it = reached.find(n);
                    if (it == reached.end()) {
                        q.push(make_pair(n, x.second+1));
                    }
                }
            }

            return ans;
        }

        int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
            vector<vector<int>> route(wordList.size());
            int b;
            int e;
            for (int i=0; i<wordList.size(); i++) {
                for (int j=0; j<wordList.size(); j++) {
                    if (i != j) {
                        if (isNear(wordList[i], wordList[j])) {
                            route[i].push_back(j);
                        }
                    }
                }
                if (endWord == wordList[i]) {
                    e = i;
                }
            }

            int ans = 100000000;
            for (int i=0; i<wordList.size(); i++) {
                if (isNear(beginWord,  wordList[i])) {
                    ans = std::min(ans, bfs(i, e, route));
                }
            }

            return ans;
        }
};


static void BM_best(benchmark::State& state) {
    /*
    Solution s;
    for (auto _ : state)
        s.restoreIpAddresses("25525511135");
        */
}

TEST(TestMine, HandleException) {
    Solution s;
    std::vector<std::string> wordList = {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"};
    EXPECT_EQ(15, s.ladderLength("qa", "sq", wordList));
}

TEST(TestMine, HandleNoraml) {
    Solution s;
    std::vector<std::string> wordList = {"hot","dot","dog","lot","log","cog"};
    EXPECT_EQ(5, s.ladderLength("hit", "cog", wordList));
}

static void BM_mine(benchmark::State& state) {
    /*
    Solution s;
    for (auto _ : state)
        s.restoreIpAddresses("25525511135");
        */
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

