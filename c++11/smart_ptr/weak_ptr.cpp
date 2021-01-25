#include <memory>
#include <iostream>

class foo {
public:
    foo() {
        std::cout << "foo construct.." << std::endl;
    }

    void method() {
        std::cout << "welcome Test foo.." << std::endl;
    }

    ~foo() {
        std::cout << "foo destruct.." << std::endl;
    }
};

int main() {
    // weak_ptr
    foo* foo2 = new foo();

    // share_ptr 管理对象
    std::shared_ptr<foo> shptr_foo2(foo2);

    // weak_ptr 弱引用
    std::weak_ptr<foo> weak_foo2(shptr_foo2);

    // 如果要获取数据指针，需要通过lock接口获取
    weak_foo2.lock()->method();

    std::shared_ptr<foo> tmp =  weak_foo2.lock();

    // 我们这边有尝试多次获取所有权（lock），看一下引用计数个数
    std::cout << "shptr_foo2 RefCount: " << weak_foo2.lock().use_count() << std::endl;

    return 0;
}

