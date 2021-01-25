/*
 * 运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。
 *
 * 获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
 * 写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。
 *
 * 进阶:
 * 你是否可以在 O(1) 时间复杂度内完成这两种操作？
 *
 * 示例:
 LRUCache cache = new LRUCache(2); // 缓存容量
 cache.put(1, 1);
 cache.put(2, 2);
 cache.get(1);       // 返回  1
 cache.put(3, 3);    // 该操作会使得密钥 2 作废
 cache.get(2);       // 返回 -1 (未找到)
 cache.put(4, 4);    // 该操作会使得密钥 1 作废
 cache.get(1);       // 返回 -1 (未找到)
 cache.get(3);       // 返回  3
 cache.get(4);       // 返回  4
 */
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

using namespace std;

struct Node
{
    int key;
    int val;
    Node* left;
    Node* right;

    Node(int k, int v): key(k), val(v), left(NULL), right(NULL) {}

};

class LRUCache {
    public:
        LRUCache(int capacity) {
            mCapacity = 0;
            mStored = 0;
            head = NULL;
            tail = NULL;

            if (capacity > 0) {
                mCapacity = capacity;
                mData.assign(capacity, Node(0, 0));
            }
        }

        int get(int key) {
            auto it = mDict.find(key);
            if (it == mDict.end()) {
                return -1;
            }
            moveToTail(it->second);

            return tail->val;
        }

        void put(int key, int value) {
            if (mCapacity <= 0) {
                return;
            }

            auto it = mDict.find(key);
            if (it != mDict.end()) {
                // 已存在缓存中的key，更新其val，将其移动到队尾即可
                it->second->val = value;
                moveToTail(it->second);
                return;
            }
            if (mStored < mCapacity) {
                // 缓存还未放满
                Node* p = &mData[mStored];

                p->key = key;
                p->val = value;

                if (mStored == 0) {
                    head = p;
                    tail = p;
                } else {
                    tail->right = p;
                    p->left = tail;
                    p->right = NULL;
                    tail = p;
                }

                mDict.insert({key, p});
                mStored++;    
            } else {
                // 缓存已满，清除最久未使用的缓存值
                Node* p = head;

                head = head->right;

                if (head != NULL) {
                    head->left = NULL;
                }

                mDict.erase(p->key);

                p->key = key;
                p->val = value;

                tail->right = p;
                p->left = tail;
                p->right = NULL;
                tail = p;

                mDict.insert({key, p});
            }
        }
    private:
        unordered_map<int, Node*> mDict;

        Node* head;
        Node* tail;

        vector<Node> mData;

        int mCapacity;
        int mStored;

        void moveToTail(Node* cur) {
            if (cur == tail) {
                return;
            }

            auto nl = cur->left;
            auto nr = cur->right;

            if (nl == NULL) {
                head = nr;
            } else {
                nl->right = nr;
            }

            nr->left = nl;

            tail->right = cur;
            cur->left = tail;
            cur->right = NULL;    

            tail = cur;
        }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main(int argc, const char** argv) {
    Solution s;
    LRUCache obj = new LRUCache(capacity);
    int param_1 = obj.get(key);
    obj.put(key,value);
}
