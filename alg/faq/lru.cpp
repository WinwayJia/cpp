#include <iostream>
#include <list>
#include <unordered_map>

class LRU {
public:
    LRU(int cap) : cap_(cap) {}

    void Put(int key, int val) {
        auto it = dict_.find(key);
        if (it != dict_.end()) {
            it->second.val_ = val;
            return;
        }

        if (dict_.size() >= cap_) {
            // erase expired item
            auto key = list_.back();
            dict_.erase(key);
            list_.pop_back();
        }

        list_.push_front(key);
        auto b = list_.begin();
        dict_.emplace(key, NodeValue(list_.begin(), val));
    }

    int Get(int key) {
        int val = 0;

        auto it = dict_.find(key);
        if (it == dict_.end()) {
            return val;
        }

        list_.splice(list_.begin(), list_, it->second.iter_);

        return it->second.val_;
    }

    struct NodeValue {
        NodeValue() {}
        NodeValue(std::list<int>::iterator it, int val) : iter_(it), val_(val) {}
        std::list<int>::iterator iter_;
        int val_;
    };

private:
    int cap_;
    std::unordered_map<int, NodeValue> dict_;
    std::list<int> list_;
};

int main() {
    LRU cache(8);

    for (int i = 0; i < 32; i++) {
        cache.Put(i, i);
    }

    std::cout << cache.Get(1) << " " << cache.Get(10) << " " << cache.Get(20) << " "
              << cache.Get(30) << " " << cache.Get(40) << std::endl;
}