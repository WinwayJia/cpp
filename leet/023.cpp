/*
   合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
   示例:

   输入:
   [
   1->4->5,
   1->3->4,
   2->6
   ]
   输出: 1->1->2->3->4->4->5->6
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
        ListNode* mergeKLists(vector<ListNode*>& lists) {
            ListNode* tmp = NULL;
            ListNode* result = NULL;
            while (1) {
                for (auto &n : lists) {
                    if (tmp == NULL) {
                        tmp = n;
                        continue;
                    } 
                    if (n && n->val < tmp->val) {
                        tmp = n;
                        n = n->next;
                    }
                }
                if (tmp == NULL) {
                    break;
                }
                if (result) {
                    result->next = tmp;
                } else {
                    result = tmp;
                }
            }

            return result;
        }

};

int main(int argc, const char** argv) {
    Solution s;
}
