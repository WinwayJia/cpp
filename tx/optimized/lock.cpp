#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

static int g_sum = 100;
std::mutex g_mtx;

void consume() {
    while (1) {
        {
            std::lock_guard<std::mutex> guard(g_mtx);
            if (g_sum <= 0) {
                break;
            }
            g_sum --;
        }
    }
}

int main() {
    while (1) {
        std::vector<std::thread> threads;
        g_sum = 100;
        std::cout << g_sum << std::endl;
        for (int i=0; i<10; i++) {
            threads.emplace_back(std::thread(consume));
        }

        for (auto& th : threads) {
            th.join();
        }
        std::cout << g_sum << std::endl;
        usleep(500*1000);
    }
    return 0;
}
