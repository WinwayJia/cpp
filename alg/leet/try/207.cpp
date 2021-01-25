#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。
//
// 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1
// ，我们用一个匹配来表示他们：[0,1]
//
// 给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？
//
// 示例 1:
//
// 输入: 2, [[1,0]]
//输出: true
//解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
//
// 示例 2:
//
// 输入: 2, [[1,0],[0,1]]
//输出: false
//解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程
// 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
//
//
//
// 提示：
//
// 输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。
// 你可以假定输入的先决条件中没有重复的边。
// 1 <= numCourses <= 10^5
//
// Related Topics 深度优先搜索 广度优先搜索 图 拓扑排序

// leetcode submit region begin(Prohibit modification and deletion)
struct Course {
public:
    Course(int cur) : cur_(cur) {}
    void appendDep(int dep) { deps_.insert(dep); }
    void appendNeed(int need) { needs_.insert(need); }
    bool canAsBeginer() { return needs_.empty(); }

    int cur_;
    std::set<int> needs_; // 我依赖的
    std::set<int> deps_;  // 依赖我的
};

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        std::map<int, Course> courses;
        for (int i = 0; i < numCourses; i++) {
            courses.emplace(i, Course(i));
        }

        for (auto& item : prerequisites) {
            auto it = courses.find(item[0]);
            it->second.appendDep(item[1]);

            it = courses.find(item[1]);
            it->second.appendNeed(item[0]);
        }

        bool flag = false;
        std::set<int> toErase;
        while (true) {
            flag = false;
            for (auto& it : courses) {
                if (it.second.canAsBeginer()) {
                    toErase.insert(it.first);
                    flag = true;
                    for (auto i : it.second.deps_) {
                        auto iter = courses.find(i);
                        iter->second.needs_.erase(it.first);
                    }
                }
            }

            for (auto i : toErase) {
                courses.erase(i);
            }
            toErase.clear();

            if (!flag) {
                break;
            }
        }

        return courses.empty();
    }
};
// leetcode submit region end(Prohibit modification and deletion)

TEST(TestSolution, HandlerNormal) {
    Solution s;
    {
        std::vector<std::vector<int>> vec = {{1, 0}, {0, 1}};
        std::cout << s.canFinish(2, vec) << std::endl;
    }
    {
        std::vector<std::vector<int>> vec = {{1, 0}};
        std::cout << s.canFinish(2, vec) << std::endl;
    }
    {
        std::vector<std::vector<int>> vec = {{1, 0}, {2, 0}, {1, 2}};
        std::cout << s.canFinish(3, vec) << std::endl;
    }
}

static void BM_best(benchmark::State& state) {}

static void BM_mine(benchmark::State& state) {}

#ifdef _TEST_
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#else
// Register the function as abenchmark
BENCHMARK(BM_mine); //用于注册测试函数
BENCHMARK(BM_best); //用于注册测试函数
BENCHMARK_MAIN();   //程序入口
#endif
