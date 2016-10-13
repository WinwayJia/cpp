//
// Created by jiawh on 16-9-18.
// version 1.0 multi-thread not support

#ifndef CPP_EPOLLCTL_H
#define CPP_EPOLLCTL_H

#include <map>
#include <fcntl.h>

typedef void (*callback)(int fd, void* buff, int len);

class EpollCtl {
public:
    EpollCtl();
    virtual ~EpollCtl();

    int add_fd(int fd, callback cb);
    int del_fd(int fd);
    int run();
    inline void set_nonblocking(int fd) {
        int flags = fcntl(fd, F_GETFL);
        fcntl(fd, F_SETFL, O_NONBLOCK|flags);
    }

private:
    static void* epoll_maintain(void* arg);
    int m_epfd;
    std::map<int, callback> m_callback_map;
};


#endif //CPP_EPOLLCTL_H
