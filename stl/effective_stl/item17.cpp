// 使用“交换技巧”来修整过剩容量
#include <iostream>
#include <vector>
#include <string>

void test_reduce_capacity() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.reserve(100);
    std::cout << "capacity:" << vec.capacity() << " size: " << vec.size() << std::endl;
    std::vector<int>(vec).swap(vec);  // vector<int>(vec)声明临时变量(复制vec中的内容, 拷贝构造函数只分配拷贝的元素需要的内存)，swap交换，然后临时变量析构
    std::cout << "capacity:" << vec.capacity() << " size: " << vec.size() << std::endl;


    std::string s;
    s = "100000000000000000000000020000000000032032"; // 使s变大，然后删除所有 它的字符
    s = "";
    std::cout << "capacity:" << s.capacity() << " size: " << s.size() << std::endl;
    std::string(s).swap(s); // 在s上进行“收缩到合适”
    std::cout << "capacity:" << s.capacity() << " size: " << s.size() << std::endl;


    // 交换技巧的变体可以用于清除容器和减少它的容量到你的实现提供的最小值
    vector<Contestant> v;
    string s;
    vector<Contestant>().swap(v); // 清除v而且最小化它的容量
    string().swap(s); // 清除s而且最小化它的容量
}

int main(int argc, char** argv) {
    test_reduce_capacity();

    return 0;
}
