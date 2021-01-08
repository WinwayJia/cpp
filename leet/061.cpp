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

//给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
//
// 示例 1:
//
// 输入: 1->2->3->4->5->NULL, k = 2
//输出: 4->5->1->2->3->NULL
//解释:
//向右旋转 1 步: 5->1->2->3->4->NULL
//向右旋转 2 步: 4->5->1->2->3->NULL
//
//
// 示例 2:
//
// 输入: 0->1->2->NULL, k = 4
//输出: 2->0->1->NULL
//解释:
//向右旋转 1 步: 2->0->1->NULL
//向右旋转 2 步: 1->2->0->NULL
//向右旋转 3 步: 0->1->2->NULL
//向右旋转 4 步: 2->0->1->NULL
// Related Topics 链表 双指针
// 👍 387 👎 0

// leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) {
            return nullptr;
        }

        std::vector<ListNode*> vec;

        while (head != nullptr) {
            vec.push_back(head);
            head = head->next;
        }

        if (1 == vec.size()) {
            return vec[0];
        }

        k = k % vec.size();
        if (0 == k) {
            return vec[0];
        }

        int first = vec.size() - k;
        head = vec[first];
        ListNode* tmp = head;
        for (auto i = first; i < vec.size(); i++) {
            tmp->next = vec[i];
            tmp = tmp->next;
        }

        for (auto i = 0; i < first; i++) {
            tmp->next = vec[i];
            tmp = tmp->next;
        }
        tmp->next = nullptr;

        return head;
    }
};

TEST(TestSolution, HandlerNormal) {
    Solution s;
    auto print = [](ListNode* head) {
        while (head) {
            std::cout << head->val << " ";
            head = head->next;
        }
        std::cout << std::endl;
    };
    auto build_list = []() -> ListNode* {
        ListNode* n1 = new ListNode(1);
        ListNode* n2 = new ListNode(2);
        ListNode* n3 = new ListNode(3);
        ListNode* n4 = new ListNode(4);
        n1->next = n2;
        n2->next = n3;
        n3->next = n4;
        return n1;
    };

    for (int i = 0; i < 5; i++) {
        print(s.rotateRight(build_list(), i));
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
