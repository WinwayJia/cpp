/*
   给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。

   你应当保留两个分区中每个节点的初始相对位置。

   示例:

   输入: head = 1->4->3->2->5->2, x = 3
   输出: 1->2->2->4->3->5
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
void dumps(ListNode* tmp) {
    while (tmp) {                          
        cout << tmp->val << " ";           
        tmp = tmp->next;                   
    }                                      
    cout << endl;                          
}                                          


class Solution {
    public:
        ListNode* partition(ListNode* head, int x) {
            ListNode* g = NULL;
            ListNode* l = NULL;
            ListNode* rg = NULL;
            ListNode* rl = NULL;
            while (head) {
                if (head->val >= x) {
                    if (g) {
                        g->next = head;
                        g = g->next;
                    } else {
                        g = head;
                        rg = g;
                    }
                } else {
                    if (l) {
                        l->next = head;
                        l = l->next;
                    } else {
                        l = head;
                        rl = l;
                    }
                }
                head = head->next;
            }
            if (g) g->next = NULL;
            if (l) l->next = NULL;
            if (l) {
                l->next = rg;
                return rl;
            } else {
                return rg; 
            }
        }

};

int main(int argc, const char** argv) {    
    Solution s;                            

    ListNode* one = new ListNode(1);       
    ListNode* tmp = one;                   
    for (int i=2; i<6; i++) {              
        tmp->next = new ListNode(rand()%10);       
        tmp = tmp->next;                   
    }                                      
    dumps(one);                            

    dumps(s.partition(one, 10));             
} 
