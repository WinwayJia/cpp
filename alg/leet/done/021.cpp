/*
   将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

   示例：

   输入：1->2->4, 1->3->4
   输出：1->1->2->3->4->4
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
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
            ListNode data(0);
            ListNode* result = &data;

            while (l1 && l2) {
                if (l1->val > l2->val) {
                    result->next = l2; 
                    l2 = l2->next;
                } else {
                    result->next = l1;
                    l1 = l1->next;
                }
                result = result->next;
            }

            if (l2) {
                result->next = l2;
            }
            if (l1) {
                result->next = l1;
            }

            return data.next;
        }

};


int main(int argc, const char** argv) {
    Solution s;
}
