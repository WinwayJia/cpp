//
// Created by jiawh on 16-9-18.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <sys/epoll.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

int do_connect(const char* ip, int port);
int sock;

void* connection_keep_thread(void* arg) {
    int epfd = epoll_create(512);
    if (epfd < 0) {
        perror("epoll_create failed");
        return NULL;
    }

    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &event);

    struct epoll_event events[512];
    while (true) {
        int ret = epoll_wait(epfd, events, 512, 5000);
        if (ret < 0) {
            perror("epoll_wait failed");
            break;
        }
        if (ret == 0) {
            continue;
        }
        char buff[1024];
        for (int i=0; i<ret; i++) {
            int len = read(events[i].data.fd, buff, 1024);
            if (len == 0) {
                printf("peer closed the connection, reconnecting...");
                sock = do_connect("127.0.0.1", 9000);
                epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &event);
            }
        }
    }

    close(epfd);
}

int do_connect(const char* ip, int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed.");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    socklen_t  len = sizeof(struct sockaddr_in);
    int ret = connect(sock, (struct sockaddr*)&addr, len);
    if (ret < 0) {
        perror("connect failed");
        return -1;
    }

    return sock;
}

int main(int argc, char** argv) {
    int ret;
    pthread_t tid;

    signal(SIGPIPE, SIG_IGN);
    pthread_create(&tid, NULL, connection_keep_thread, NULL);
    sock = do_connect("127.0.0.1", 9000);
    while (true) {
        time_t t = time(NULL);
        const char* str = ctime(&t);
        ret = send(sock, str, strlen(str), 0);
        if (ret < 0) {
            printf("send failed: %s\n", strerror(errno));
            break;
        }
        printf("ret = %d\n", ret);
        sleep(1);
    }

    close(sock);

    return 0;
}

