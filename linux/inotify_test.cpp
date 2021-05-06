#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

bool g_isRunning = true;

void sighandler(int signo) {
    if (signo == SIGUSR1) {
        g_isRunning = false;
    }
}

int main(int argc, char **argv) {
    int length, i = 0;
    int fd;
    int wd;
    char buffer[BUF_LEN];
    if (argc < 3) {
        printf("Usage: %s monitorDir DestDir\n", argv[0]);
        exit(0);
    }

    signal(SIGUSR1, sighandler);

    fd = inotify_init1(IN_NONBLOCK);

    if (fd < 0) {
        perror("inotify_init");
    }

    char cmdStr[128];
    wd = inotify_add_watch(fd, argv[1], IN_MOVED_TO);

    do {
        if (!g_isRunning) {
            break;
        }
        i = 0;

        memset(buffer, 0, BUF_LEN);
        // 简单实现，不使用IO复用了
        length = read(fd, buffer, BUF_LEN);
        if (length < 0) {
            if (EAGAIN != errno) {
                perror("read");
            }
            sleep(1);
            continue;
        } else if (0 == length) {
            sleep(1);
            continue;
        }

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];
            if (0 == event->len) {
                break;
            }

            snprintf(cmdStr, sizeof(cmdStr), "cp %s/%s %s/%s.queue", argv[1],
                     event->name, argv[2], event->name);
            system(cmdStr);

            i += EVENT_SIZE + event->len;
        }
    } while (1);

    inotify_rm_watch(fd, wd);
    close(fd);

    exit(0);
}
