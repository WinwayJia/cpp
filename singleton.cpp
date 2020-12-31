#include <iostream>


template <typename T>
class Singleton {
public:
    template<typename... Args>
    static T& Instance(Args&&... args){
        static T t(std::forward<T>(args)...);
        return t;
    }
    
};

class Demo {
public:
    Demo(int x, int y) : x_(x) {

    }
    void show() const {
        std::cout << "x: " << &x_ << " " << x_ << std::endl;
    }

private:
    int x_;
};

int main() {
    Singleton<Demo>::Instance(2, 1).show();
    // Singleton<Demo>::Instance(2, 1).show();
    // Singleton<Demo>::Instance(2, 1).show();
}