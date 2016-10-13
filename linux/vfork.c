#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int glob = 1000;
int main(void) {
    int var;
    var = 88;
    int pid;
    //if ((pid = fork()) < 0) {
    if ((pid = vfork()) < 0) {
        printf("vfork error");
        exit(-1);
    } else if (pid == 0) { /* 子进程 */
        var++;
        //return 0;
    }
    printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);

    return 0;
}
