#include <list>
#include <string>
#include <iostream>

int main() {
    std::string h = "Hello";
    std::string w = "World";
    
    std::list<std::string> ll;
    ll.push_front(h);
    ll.push_front(w);

    for (const auto& it : ll) {
        std::cout << it << std::endl;
    }

    return 0;
}
