#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int idx = 2;

    for (int i=0; i<idx; i++) {
        fork();
        printf("[%d-->%d]: %d\n", getppid(), getpid(), i);
    }
    
    int status;
    while (wait(&status)) {
        sleep(1);
    }
    return 0;
}
