// 当使用new得指针的容器时，记得在销毁容器前delete那些指针
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

class SampleClass {

};

void Release(SampleClass* x) {
    delete x;
}

template<class T>
struct DeleteObject {//: public unary_function<const T*, void> { // 条款40描述了为什么, 这里有这个继承
    void operator()(const T* ptr) const
    {
        delete ptr;
    }
};

void test_pointer_container() {
    std::vector<std::shared_ptr<SampleClass>> vec;

    for (int i=0; i<10; i++) {
        //vec.push_back(new SampleClass);
        vec.push_back(std::shared_ptr<SampleClass>(new SampleClass));
    }

    // use
/*
    {
        for (auto x : vec) {
            delete x;
        }
    }
    */
    /*
    {
        for_each(vec.begin(), vec.end(), Release);
    }
    */
    /*
    {
        for_each(vec.begin(), vec.end(), DeleteObject<SampleClass>);
    }
    */
}

int main(int argc, char** argv) {

    test_pointer_container();

    return 0;
}
