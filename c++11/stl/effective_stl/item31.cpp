// Know your sorting options.
/*
排序 sort stable_sort
部分排序 partial_sort // 堆排序
前N个元素 nth_element // 堆排序
分割 partition stable_partion
*/
//算法sort、stable_sort、partial_sort和nth_element需要随机访问迭代器，所以它们可能只能用于vector、string、deque和数组。

/*
我们总结一下你的排序选择：
● 如果你需要在vector、string、deque或数组上进行完全排序，你可以使用sort或stable_sort。
● 如果你有一个vector、string、deque或数组，你只需要排序前n个元素，应该用partial_sort。
● 如果你有一个vector、string、deque或数组，你需要鉴别出第n个元素或你需要鉴别出最前的n个元素，
而不用知道它们的顺序，nth_element是你应该注意和调用的。
● 如果你需要把标准序列容器的元素或数组分隔为满足和不满足某个标准，你大概就要找partition或
stable_partition。
● 如果你的数据是在list中，你可以直接使用partition和stable_partition，你可以使用list的sort来代替sort和
stable_sort。如果你需要partial_sort或nth_element提供的效果，你就必须间接完成这个任务，但正如我
在上面勾画的，会有很多选择。
*/
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

void Print(int x) {
    cout << x << " ";
}

// partial_sort使用堆排序，所以只能是支持随机访问迭代器的容器
void test_partial_sort() {
    vector<int> vec = {3, 5, 8, 2, 4, 7, 1};
    for_each(vec.begin(), vec.end(), Print); cout << endl;
    //partial_sort(vec.begin(), vec.end(), vec.begin() + 1);
    partial_sort(vec.begin(), vec.begin() + 2, vec.end());
    for_each(vec.begin(), vec.end(), Print); cout << endl;
}

void test_nth_element() {
    vector<int> vec = {3, 5, 8, 2, 4, 7, 1};
    nth_element(vec.begin(), vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(), Print); cout << endl;
}

bool condition(int x) {
    return x > 3;
}

void test_partition() {
    vector<int> vec = {3, 5, 8, 2, 4, 7, 1};
    auto it = partition(vec.begin(), vec.end(), condition);
    cout << "end:" << *it << endl;
    for_each(vec.begin(), it, Print); cout << endl;
    for_each(vec.begin(), vec.end(), Print); cout << endl;
}

void test_partial_sort_on_list() {
    list<int> ll = {3, 5, 8, 2, 4, 7, 1};

    vector<list<int>::const_iterator> tmp;
    for (auto it(ll.begin()), end(ll.end()); it != end; ++it) {
        tmp.push_back(it);
    }
    partial_sort(tmp.begin(), tmp.end()+2, tmp.end());
    std::list<list<int>::const_iterator> result;
    for (auto it(tmp.begin()), end(tmp.end()); it != end; ++it) {
        result.splice(result.begin(), ll, it);
    }
}

int main(int argc, char** argv) {
    test_partial_sort();

    cout << "nth_element" << endl;
    test_nth_element();

    cout << "partition" << endl;
    test_partition();

    cout << "partial_sort on list" << endl;
    test_partial_sort_on_list();

    return 0;
}
