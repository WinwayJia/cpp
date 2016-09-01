#include <stdio.h>
//#define _GNU_SOURCE
#include <sched.h>

int bind_cpu() {
    unsigned long mask = 2; /* processors 0, 1, and 2 */
    unsigned int len = sizeof(mask);

    if (sched_setaffinity(0, len, &mask) < 0) {
        perror("sched_setaffinity");
        return -1;
    }

    return 0;
}

int get_cpu() {
    unsigned long mask;
    unsigned int len = sizeof(mask);

    if (sched_getaffinity(0, len, &mask) < 0) {
        perror("sched_getaffinity");
        return -1;
    }

    printf("my affinity mask is: %08lx\n", mask);
    printf("my affinity mask is: %08x\n", mask);

    return 0;
}

int main(int argc, char** argv) {
//    bind_cpu();
    get_cpu();

    return 0;
}
