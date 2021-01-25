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


/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            auto size = lists.size();
            if (0 == size) {
                return nullptr;
            }
            if (1 == size) {
                return lists[0];
            }
            auto it = lists.begin();
            int pos = size / 2;
            std::advance(it, pos);
            auto right = vector<ListNode*>(it, lists.end());
            auto left = vector<ListNode*>(lists.begin(), it);

            auto l = left.size() > 1 ? mergeKLists(left) : left[0];
            auto r = right.size() > 1 ? mergeKLists(right) : right[0];

            ListNode* ans = nullptr;
            if (!r) {
                return l;
            }
            if (!l) {
                return r;
            }
            if (l->val > r->val) {
                ans = r;
                r = r->next;
            } else {
                ans = l;
                l = l->next;
            }
            while (l && r) {
                if (l->val > r->val) {
                    ans->next = r;
                    r = r->next;
                    ans = ans->next;
                } else {
                    ans->next = l;
                    l = l->next;
                    ans = ans->next;
                }
            }
            if (r) {
                ans->next = r;
            }
            if (l) {
                ans->next = l;
            }

            return ans;
        }
};


// [[1,4,5],[1,3,4],[2,6]]
TEST(TestSolution, HandlerNormal) {
    vector<vector<int>> vec = {{1,4,5},{1,3,4},{2,6}};
    auto generate_list = [](vector<int>& nums) -> ListNode* {
        if (nums.empty()) {
            return nullptr;
        }
        ListNode* tmp = new ListNode(nums[0]);
        auto ret = tmp;
        for (int i=1; i<nums.size(); i++) {
            tmp->next = new ListNode(nums[i]);
            tmp = tmp->next;
        }
        return ret;
    };

    vector<ListNode*> lists = {
        generate_list(vec[0]),
        generate_list(vec[1]),
//        generate_list(vec[2])
    };

    Solution s;
    s.mergeKLists(lists);
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

