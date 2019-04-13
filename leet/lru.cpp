#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

class LRUCache{
  private:
    struct CacheNode {
      int key;
      int value;
      CacheNode(int k, int v) :key(k), value(v){}
    };
  public:
    LRUCache(int capacity) {
      this->capacity = capacity;
    }

    int get(int key) {
      if (cacheMap.find(key) == cacheMap.end()) return -1;
      // 把当前访问的节点移到链表头部，并且更新 map 中该节点的地址
      cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
      cacheMap[key] = cacheList.begin();
      return cacheMap[key]->value;
    }

    void set(int key, int value) {
      if (cacheMap.find(key) == cacheMap.end()) {
        if (cacheList.size() == capacity) { //删除链表尾部节点（最少访问的节点）
          cacheMap.erase(cacheList.back().key);
          cacheList.pop_back();
        }
        // 插入新节点到链表头部, 并且在 map 中增加该节点
        cacheList.push_front(CacheNode(key, value));
        cacheMap[key] = cacheList.begin();
      } else {
        //更新节点的值，把当前访问的节点移到链表头部, 并且更新 map 中该节点的地址
        cacheMap[key]->value = value;
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
      }
    }
  private:
    list<CacheNode> cacheList;
    unordered_map<int, list<CacheNode>::iterator> cacheMap;
    int capacity;
};

int main() {
  LRUCache cache(2);
  cache.set(1, 10);
  cache.set(2, 20);
  cache.set(3, 30);

  cout << cache.get(1) << endl;
  cout << cache.get(2) << endl;
  cout << cache.get(3) << endl;

  return 0;
}
