#include <cassert>
#include <iostream>
#include <string>

struct Head {
    int64_t len_;
    int64_t cap_;
    int64_t ref_;

    void show() const {
        std::cout << "len: " << len_ << " cap: " << cap_ << " ref: " << ref_ << std::endl;
    }
};

Head* getHead(const std::string& str) {
    char* ptr = (char*)(*(void**)(&str));
    std::cout << ptr << std::endl;
    Head* h = (Head*)(ptr - sizeof(Head));

    return h;
}

std::string basic() {
    std::string str = "hello";

    Head* h = getHead(str);
    {
        std::string str2 = str;
        h->show();
    }
    std::string str3 = str;
    h->show();

    return str;
}

void read() {
    std::string a = "some string";
    std::string b = a;
    assert(b.data() == a.data()); // We assume std::string is COW-ed
    printf("ptr: a: %p b: %p\n", a.data(), b.data());

    // std::cout << b[0] << std::endl;
    const char& c = b[0];
    assert(b.data() != a.data()); // Oops!
    printf("ptr: a: %p b: %p\n", a.data(), b.data());
}

void sso() {
    std::string a = "hello world";
    std::string b = a;
    assert(a.data() == b.data());
    std::cout << std::boolalpha << (a.data() == b.data()) << std::endl;
}

int main() {
    sso();
    return 0;
    std::string a = std::string("hello");
    a += std::to_string(time(nullptr));
    a.reserve(255);
    std::string b = a;

    auto size = b.size();
    const char* ptr = b.data();
    // (const_cast<char*>(ptr))[0] = '1';

    std::cout << a << std::endl;
    std::cout << b << size << std::endl;

    std::string x = basic();

    Head* h = getHead(x);
    h->show();

    read();
    return 0;
}