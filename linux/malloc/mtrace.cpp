#include <mcheck.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <mcheck.h>
#include <unistd.h>

void signal_handler(int sig_num) {
    if (sig_num == SIGUSR1) {
        mtrace();
    } else if (sig_num == SIGUSR2) {
        muntrace();
    }
}

int main(int argc, char *argv[]) {
    signal(SIGUSR1, signal_handler);
    int j;
    //    mtrace();

    for (j = 0; j < 2; j++)
        malloc(100);            /* Never freed--a memory leak */

    while (1) {
        calloc(16, 16);             /* Never freed--a memory leak */
        sleep(1);
        j ++;
        if (j > 30) {
            break;
        }
    }
    printf("exiting...");
    exit(EXIT_SUCCESS);
}

