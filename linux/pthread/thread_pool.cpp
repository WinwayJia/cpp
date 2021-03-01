#include <functional>
#include <iostream>
#include <pthread.h>

class ThreadPool {
public:
    void Init(int num) {
        threads_ = new pthread_t[num];
        for (int i = 0; i < num; i++) {
            // pthread_create(&threads_[i], nullptr, thread_fn, nullptr);
            pthread_create(&threads_[i], nullptr, &ThreadPool::thread_fn, this);
        }

        pthread_mutex_init(&mutex_, nullptr);
    }

    static void* thread_fn(void* arg) {
        ThreadPool* ptr = (ThreadPool*)arg;
        std::cout << arg << std::endl;
        while (!ptr->exit_) {
            pthread_mutex_lock(&ptr->mutex_);

            pthread_mutex_unlock(&ptr->mutex_);
        }

        return nullptr;
    };

    void Enqueue(std::function<void()> fn) {}

private:
    pthread_t* threads_;
    pthread_mutex_t mutex_;
    bool exit_;
};

int main(int argc, char const* argv[]) { return 0; }
