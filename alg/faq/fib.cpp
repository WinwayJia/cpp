#include <iostream>

// 递归
int fib(int n) {
    if (n <= 2) {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

// dp
int fib_dp(int n) {
    if (n <= 2) {
        return 1;
    }

    int pre = 1;
    int suf = 1;

    for (int i = 3; i <= n; i++) {
        int tmp = suf;
        suf = pre + suf;
        pre = tmp;
    }

    return suf;
}

int main(int argc, char const *argv[]) {
    std::cout << fib(10) << std::endl;
    std::cout << fib_dp(10) << std::endl;
    return 0;
}
