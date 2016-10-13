//
// Created by jiawh on 16-9-18.
//

#include <sys/epoll.h>
#include <unistd.h>
#include <thread_db.h>
#include "EpollCtl.h"


EpollCtl::EpollCtl() {
    m_epfd = epoll_create(512);
}

EpollCtl::~EpollCtl() {
    if (m_epfd >= 0) {
        close(m_epfd);
    }
}

int EpollCtl::add_fd(int fd, callback cb) {
    printf("epoll add fd: %d\n", fd);
    set_nonblocking(fd);

    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = fd;

    m_callback_map.insert(std::pair<int, callback>(fd, cb));
    int ret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &event);
    if (ret < 0) {
        perror("epoll_ctl failed");
        return -1;
    }

    return 0;
}

int EpollCtl::del_fd(int fd) {
    printf("epoll del fd: %d\n", fd);
    int ret = epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, NULL);
    if (ret < 0) {
        perror("epoll_ctl failed");
        return -1;
    }

    m_callback_map.erase(fd);
    return 0;
}

int EpollCtl::run() {
    thread_t tid;
    pthread_create(&tid, NULL, EpollCtl::epoll_maintain, this);
}

void* EpollCtl::epoll_maintain(void *arg) {
    EpollCtl* epollCtl = (EpollCtl*)arg;
    int ret;
    struct epoll_event events[512];
    printf("epfd = %d\n", epollCtl->m_epfd);

    while (true) {
        ret = epoll_wait(epollCtl->m_epfd, events, 512, 5000);
        if (ret < 0) {
            perror("epoll_wait failed");
            break;
        }
        if (ret == 0) {
            printf("epoll_wait timeout\n");
            continue;
        }

        for (int i=0; i<ret; i++) {
            char buff[1024] = {0};
            int fd = events[i].data.fd;
            auto iter = epollCtl->m_callback_map.find(fd);
            callback cb = (callback)(iter->second);

            int len = read(fd, buff, 1024);
            if (0 == len) {
                printf("connection closed by server\n");
                epollCtl->del_fd(fd);
                cb(fd, NULL, 0);
                continue;
            }
            cb(fd, buff, len);
        }
    }

//    delete arg;
}