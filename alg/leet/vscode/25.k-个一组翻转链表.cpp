/*
 * @lc app=leetcode.cn id=25 lang=cpp
 *
 * [25] K 个一组翻转链表
 */
#include "head.h"
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// @lc code=start
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr) {
            return nullptr;
        }
        if (k <= 1) {
            return head;
        }
        ListNode* ans = head;

        vector<int> vals;
        deque<int> dq;
        while (head) {
            dq.push_back(head->val);
            head = head->next;

            if (dq.size() == k) {
                while (!dq.empty()) {
                    vals.push_back(dq.back());
                    dq.pop_back();
                }
            }
        }

        while (!dq.empty()) {
            vals.push_back(dq.front());
            dq.pop_front();
        }

        auto tmp = ans;
        for (int i = 0; i < vals.size(); i++) {
            tmp->val = vals[i];
            tmp = tmp->next;
        }

        return ans;
    }
};
// @lc code=end

int main(int argc, char const* argv[]) {
    ListNode* one = new ListNode(1);
    ListNode* two = new ListNode(2);
    ListNode* three = new ListNode(3);
    ListNode* four = new ListNode(4);
    ListNode* five = new ListNode(5);
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = five;

    Solution s;
    auto ans = s.reverseKGroup(one, 3);

    while (ans) {
        cout << ans->val << " ";
        ans = ans->next;
    }
    cout << endl;

    return 0;
}
