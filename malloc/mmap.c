#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    void* addr = mmap(NULL, sizeof(int) * 3,
            PROT_READ|PROT_WRITE,
            MAP_ANON|MAP_SHARED, -1, 0); 

    int* ptr;
    for (int i=0; i<3; i++) {
        pid_t pid = fork();
        if (0 == pid) {
            // child
            ptr = (int*)addr;
            ptr[i] = i + 3;
            printf("child: %d %d %d %d\n", getpid(), ptr[0], ptr[1], ptr[2]);
            exit(0);
        } else if (pid > 0) {
            // parent
        } else {
            // error
        }
    }
    
    sleep(1);
    ptr = (int*)addr;
    printf("%d %d %d\n", ptr[0], ptr[1], ptr[2]);
}
