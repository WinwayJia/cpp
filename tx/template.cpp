#include <iostream>

template<class T>
T xxx(int x) {
    if (x > 10) {
        return "error";
    }

    return x;
}

int main() {
    xxx<int>(10);
}
