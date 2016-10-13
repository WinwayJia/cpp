#include <cstdlib>
#include <unistd.h>
#include <climits>
#include <stdint.h>
#include <cstdio>
#include <cerrno>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <sys/sysinfo.h>
#include <memory>

#include "epoll_socket.h"
#include "simple_log.h"

CEpollSocket::CEpollSocket() {
    m_thread_pool = NULL;
    m_use_default_tp = true;
}

CEpollSocket::~CEpollSocket() {
    if (m_thread_pool != NULL && m_use_default_tp) {
        delete m_thread_pool;
        m_thread_pool = NULL;
    }
}

int CEpollSocket::setNonblocking(int fd) {
    int flags;

    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int CEpollSocket::bind_on(unsigned int ip) {
    /* listen on sock_fd, new connection on new_fd */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        LOG_ERROR("socket error:%s", strerror(errno));
        return -1;
    }
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(m_port);
    my_addr.sin_addr.s_addr = ip;

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) < 0) {
        LOG_ERROR("bind error:%s", strerror(errno));
        return -1;
    }
    if (listen(sockfd, m_backlog) < 0) {
        LOG_ERROR("listen error:%s", strerror(errno));
        return -1;
    }
    m_listen_sockets.insert(sockfd);
    return 0;
}

int CEpollSocket::listen_on() {
    int ret = 0;
    if (m_bind_ips.empty()) {
        ret = bind_on(INADDR_ANY); /* auto-fill with my IP */
        if (ret != 0) {
            return ret;
        }
        LOG_INFO("bind for all ip (0.0.0.0)!");
    } else {
        for (size_t i = 0; i < m_bind_ips.size(); i++) {
            unsigned ip = inet_addr(m_bind_ips[i].c_str());
            ret = bind_on(ip);
            if (ret != 0) {
                return ret;
            }
            LOG_INFO("bind for ip:%s success", m_bind_ips[i].c_str());
        }
    }

    LOG_INFO("start Server Socket on port : %d", m_port);
    return 0;
}

int CEpollSocket::accept_socket(int sockfd, std::string &client_ip) {
    int new_fd;
    struct sockaddr_in their_addr; /* connector's address information */
    socklen_t sin_size = sizeof(struct sockaddr_in);

    if (-1 == (new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size))) {
        LOG_ERROR("accept error:%s", strerror(errno));
        return -1;
    }

    client_ip = inet_ntoa(their_addr.sin_addr);
    LOG_DEBUG("server: got connection from %s\n", client_ip.c_str());
    return new_fd;
}

int CEpollSocket::handle_accept_event(int epollfd, epoll_event &event, CEpollSocketWatcher &socket_handler) {
    int sockfd = event.data.fd;

    std::string client_ip;
    int conn_sock = accept_socket(sockfd, client_ip);
    if (conn_sock == -1) {
        return -1;
    }
    setNonblocking(conn_sock);
    LOG_DEBUG("get accept socket which listen fd:%d, conn_sock_fd:%d", sockfd, conn_sock);

    CEpollContext *epoll_context = new CEpollContext();
    epoll_context->fd = conn_sock;
    epoll_context->client_ip = client_ip;

    socket_handler.on_accept(*epoll_context);

    struct epoll_event conn_sock_ev;
    conn_sock_ev.events = EPOLLIN;
    conn_sock_ev.data.ptr = epoll_context;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &conn_sock_ev) == -1) {
        LOG_ERROR("epoll_ctl: conn_sock:%s", strerror(errno));
        return -1;
    }

    return 0;
}

void* read_func(void *data) {
    std::unique_ptr<TaskData> tdata((TaskData*)data);
    int epollfd = tdata->epollfd;
    epoll_event event = (tdata->event);
    CEpollSocketWatcher &socket_handler = *(tdata->watcher);

    CEpollContext *epoll_context = (CEpollContext *) event.data.ptr;
    int fd = epoll_context->fd;

    int ret = socket_handler.on_readable(epollfd, event);
    if (ret == READ_CLOSE) {
        close_and_release(epollfd, event, socket_handler);
        return NULL;
    }
    if (ret == READ_CONTINUE) {
        event.events = EPOLLIN;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    } else if (ret == READ_OVER) { // READ_OVER
        event.events = EPOLLOUT;
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    } else {
        LOG_ERROR("unkonw ret!");
    }

    return NULL;
}

int CEpollSocket::handle_readable_event(int epollfd, epoll_event &event, CEpollSocketWatcher &socket_handler) {
    CEpollContext *epoll_context = (CEpollContext *) event.data.ptr;
    int fd = epoll_context->fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event); // TODO remove event or use EPOLLET?

    TaskData *tdata = new TaskData();
    tdata->epollfd = epollfd;
    tdata->event = event;
    tdata->watcher = &socket_handler;

    CTask *task = new CTask(read_func, tdata);
    int ret = m_thread_pool->add_task(task);
    if (ret != 0) {
        LOG_WARN("add read task fail:%d, we will close connect.", ret);
        close_and_release(epollfd, event, socket_handler);
    }
    return ret;
}

void* write_func(void *data) {
    std::unique_ptr<TaskData> tdata((TaskData*)data);
    int epollfd = tdata->epollfd;
    epoll_event event = (tdata->event);
    CEpollSocketWatcher &socket_handler = *(tdata->watcher);

    CEpollContext *epoll_context = (CEpollContext *) event.data.ptr;
    int fd = epoll_context->fd;
    LOG_DEBUG("start write data");

    int ret = socket_handler.on_writeable(*epoll_context);
    if (ret == WRITE_CONN_CLOSE) {
        close_and_release(epollfd, event, socket_handler);
        return NULL;
    }

    if (ret == WRITE_CONN_CONTINUE) {
        event.events = EPOLLOUT;
    } else {
        event.events = EPOLLIN;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    return NULL;
}

int CEpollSocket::handle_writeable_event(int epollfd, epoll_event &event, CEpollSocketWatcher &socket_handler) {
    CEpollContext *epoll_context = (CEpollContext *) event.data.ptr;
    int fd = epoll_context->fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event);

    TaskData *tdata = new TaskData();
    tdata->epollfd = epollfd;
    tdata->event = event;
    tdata->watcher = &socket_handler;

    CTask *task = new CTask(write_func, tdata);
    int ret = m_thread_pool->add_task(task);
    if (ret != 0) {
        LOG_WARN("add write task fail:%d, we will close connect.", ret);
        close_and_release(epollfd, event, socket_handler);
    }
    return ret;
}

void CEpollSocket::set_thread_pool(CThreadPool *tp) {
    this->m_thread_pool = tp;
    m_use_default_tp = false;
}

int CEpollSocket::start_epoll(int port, CEpollSocketWatcher &socket_handler, int backlog, int max_events) {
    m_backlog = backlog;
    m_port = port;

    if (m_thread_pool == NULL) {
        int core_size = get_nprocs();
        LOG_INFO("thread pool not set, we will build for core size:%d", core_size);
        m_thread_pool = new CThreadPool();
        m_thread_pool->set_pool_size(core_size);
    }
    int ret = m_thread_pool->start();
    if (ret != 0) {
        LOG_ERROR("thread pool start error:%d", ret);
        return ret;
    }
    ret = this->listen_on();
    if (ret != 0) {
        return ret;
    }

    // the size argument is ignored
    // The "size" parameter is a hint specifying the number of file
    // descriptors to be associated with the new instance.
    int epollfd = epoll_create(1024);
    if (-1 == epollfd) {
        LOG_ERROR("epoll_create:%s", strerror(errno));
        return -1;
    }

    for (auto i = m_listen_sockets.begin(); i != m_listen_sockets.end(); i++) {
        int sockfd = *i;
        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = sockfd;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
            LOG_ERROR("epoll_ctl: listen_sock:%s", strerror(errno));
            return -1;
        }
    }

    epoll_event *events = new epoll_event[max_events];
    while (1) {
        int fds_num = epoll_wait(epollfd, events, max_events, -1);
        if (-1 == fds_num) {
            if (errno == EINTR) { // The call was interrupted by a signal handler
                continue;
            }
            LOG_ERROR("epoll_pwait:%s", strerror(errno));
            break;
        }

        for (int i = 0; i < fds_num; i++) {
            if (m_listen_sockets.count(events[i].data.fd)) {
                // accept connection
                this->handle_accept_event(epollfd, events[i], socket_handler);
            } else if (events[i].events & EPOLLIN) {
                // readable
                this->handle_readable_event(epollfd, events[i], socket_handler);
            } else if (events[i].events & EPOLLOUT) {
                // writeable
                this->handle_writeable_event(epollfd, events[i], socket_handler);
            } else {
                LOG_INFO("unkonw events :%d", events[i].events);
            }
        }
    }
    if (events != NULL) {
        delete[] events;
        events = NULL;
    }
    return -1;
}

int close_and_release(int epollfd, epoll_event &epoll_event, CEpollSocketWatcher &socket_handler) {
    if (NULL == epoll_event.data.ptr) {
        return 0;
    }
    LOG_DEBUG("connect close");

    CEpollContext *hc = (CEpollContext *) epoll_event.data.ptr;
    socket_handler.on_close(*hc);

    int fd = hc->fd;
    epoll_event.events = EPOLLIN | EPOLLOUT;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &epoll_event);

    delete (CEpollContext *) epoll_event.data.ptr;
    epoll_event.data.ptr = NULL;

    int ret = close(fd);
    LOG_DEBUG("connect close complete which fd:%d, ret:%d", fd, ret);
    return ret;
}

void CEpollSocket::add_bind_ip(const std::string& ip) {
    m_bind_ips.push_back(ip);
}
