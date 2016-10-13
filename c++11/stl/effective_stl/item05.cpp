// 尽量使用区间成员函数代替它们的单 元素兄弟 
// 尽量使用区间成员函数代替它们的单元素兄弟的理由。
// ● 一般来说使用区间成员函数可以输入更少的代码。
// ● 区间成员函数会导致代码更清晰更直接了当。

// 应该尽量避免手写显式循环
// 几乎所有目标区间被插入迭代器指定的copy的使用都可以用调用的区间成员函数的来代替。

// 当处理标准序列容器时，应用单元素成员函数比完成同样目的的区间成员函数需要更多地内存分配，更频繁地拷贝对象，而且/或者造成多余操作。
#include <vector>
#include <iostream>
#include <set>

void test_half_vector() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 2};

    //std::vector<int> vec2(vec1.begin() + vec1.size()/2, vec1.end());
    std::vector<int> vec2;
    {
        vec2.assign(vec1.begin() + vec1.size()/2, vec1.end());
    }
    {
        copy(vec1.begin() + vec1.size() / 2, vec1.end(), back_inserter(vec2));
    }
    {
        for (auto it = vec1.begin() + vec1.size()/2; it != vec1.end(); ++it) {
            vec2.push_back(*it);
        }
    }
    {
        vec2.insert(vec2.end(), vec1.begin()+vec1.size()/2, vec1.end());
    }

    for (auto x : vec2) {
        std::cout << x << " " ;
    }
    std::cout << std::endl;

    // 关联容器的区间插入可能变得比单元素插入更有效。毫无疑问它们不会降低效率，所以你选择它们没有任何损失。
    std::set<int> ss(vec1.begin(), vec1.end());
//    ss.insert(vec1.begin(), vec1.end());
    for (auto x : ss) {
        std::cout << x << " ";
    }
    std::cout << "set size: " << ss.size() << std::endl;
}

int main(int argc, char** argv) {
    test_half_vector();

    return 0;
}


/* 
● 区间构造。所有标准容器都提供这种形式的构造函数：
container::container(InputIterator begin, // 区间的起点
InputIterator end); // 区间的终点

● 区间插入。所有标准序列容器都提供这种形式的insert：
void container::insert(iterator position, // 区间插入的位置
InputIterator begin, // 插入区间的起点
InputIterator end); // 插入区间的终点
关联容器使用它们的比较函数来决定元素要放在哪里，所以它们了省略position参数。
void container::insert(lnputIterator begin, InputIterator end);

● 区间删除。每个标准容器都提供了一个区间形式的erase，但是序列和关联容器的返回类型不同。序列容器提供
了这个：
iterator container::erase(iterator begin, iterator end);
而关联容器提供这个：
void container::erase(iterator begin, iterator end);

● 区间赋值。就像我在这个条款的一开始提到的，所有标准列容器都提供了区间形式的assign：
void container::assign(InputIterator begin, InputIterator end);
*/
