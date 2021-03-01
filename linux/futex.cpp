#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int before = 1;
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int after = 2;

void* thread_func(void* arg) {
    auto mutex = (pthread_mutex_t*)(arg);

    while (1) {
        pthread_mutex_lock(mutex);
        printf("thread enter lock\n");
        sleep(1);
        pthread_mutex_unlock(mutex);
        printf("thread leave lock\n");
    }

    return nullptr;
}

int main(int argc, char const* argv[]) {
    int counter = 0;
    auto ret = __sync_bool_compare_and_swap(&counter, 0, 1);
    printf("ret: %d counter: %d\n", ret, counter);
    // pthread_mutex_init(&mutex, nullptr);
    pthread_t thread;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    mutex.__data.__lock = 1;
    printf("mutex addr: %p\n", &mutex);
    pthread_create(&thread, nullptr, thread_func, &mutex);
    while (1) {
        pthread_mutex_lock(&mutex);
        printf("main enter lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        printf("main leave lock\n");
    }

    return 0;
}
