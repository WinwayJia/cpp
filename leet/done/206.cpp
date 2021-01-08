/*
   反转一个单链表。

   示例:
   输入: 1->2->3->4->5->NULL
   输出: 5->4->3->2->1->NULL
   进阶:
   你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
   */
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <iostream>
#include <unordered_map>

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
        ListNode* reverseList(ListNode* head) {
            if (head == NULL) {
                return head;
            }
            ListNode* curr = head;
            ListNode* next = head->next;
            head->next = NULL;
            ListNode* tmp = NULL;
            while (next != NULL) {
                tmp = next->next;
                next->next = curr;
                curr = next;
                next = tmp;
            }
            return curr;
        }

};

void dumps(ListNode* tmp) {
    while (tmp) {
        cout << tmp->val << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

int main(int argc, const char** argv) {
    Solution s;

    ListNode* one = new ListNode(1);
    ListNode* tmp = one;
    for (int i=2; i<6; i++) {
        tmp->next = new ListNode(i);
        tmp = tmp->next;
    }
    dumps(one);

    dumps(s.reverseList(one));
}
