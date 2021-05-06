#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_spinlock_t lock;

void* thread_func(void* arg) {
    printf("%s\n", __FUNCTION__);
    pthread_spin_lock(&lock);
    printf("%s\n", __FUNCTION__);
}

int main(int argc, char const* argv[]) {
    int ret = pthread_spin_init(&lock, PTHREAD_PROCESS_SHARED);

    printf("%s\n", __FUNCTION__);
    pthread_spin_lock(&lock);
    printf("%s\n", __FUNCTION__);

    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    sleep(3);
    pthread_spin_unlock(&lock);
    pthread_join(tid, NULL);

    return 0;
}
