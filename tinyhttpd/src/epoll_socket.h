#ifndef __EPOLL_SOCKET_H__
#define __EPOLL_SOCKET_H__

#include <sys/epoll.h>
#include <vector>
#include <set>
#include <string>

#include "thread_pool.h"

#define SS_WRITE_BUFFER_SIZE 4096
#define SS_READ_BUFFER_SIZE 4096

#define WRITE_CONN_ALIVE 0
#define WRITE_CONN_CLOSE 1
#define WRITE_CONN_CONTINUE 2

#define READ_OVER 0
#define READ_CONTINUE 1
#define READ_CLOSE -1

class CEpollContext {
public:
	void *ptr;
	int fd;
	std::string client_ip;
};

typedef void (*ScheduleHandlerPtr)();

class CEpollSocketWatcher {
public:
	virtual int on_accept(CEpollContext &epoll_context) = 0;

	virtual int on_readable(int epollfd, epoll_event &event) = 0;

	//return :
	//if return value == 1, we will close the connection
	//if return value == 2, we will continue to write
	virtual int on_writeable(CEpollContext &epoll_context) = 0;

	virtual int on_close(CEpollContext &epoll_context) = 0;

};

struct TaskData {
	int epollfd;
	epoll_event event;
	CEpollSocketWatcher *watcher;
};

int close_and_release(int epollfd, epoll_event &event,
		CEpollSocketWatcher &socket_watcher);

class CEpollSocket {
public:
	CEpollSocket();

	virtual ~CEpollSocket();

	int start_epoll(int port, CEpollSocketWatcher &socket_watcher, int backlog,
			int max_events);

	void set_thread_pool(CThreadPool *tp);

	void set_schedule(ScheduleHandlerPtr h);

	void add_bind_ip(const std::string& ip);
private:
	int setNonblocking(int fd);

	int accept_socket(int sockfd, std::string &client_ip);

	inline int bind_on(unsigned int ip);

	int listen_on();

	int handle_accept_event(int epollfd, epoll_event &event,
			CEpollSocketWatcher &socket_watcher);

	int handle_readable_event(int epollfd, epoll_event &event,
			CEpollSocketWatcher &socket_watcher);

	int handle_writeable_event(int epollfd, epoll_event &event,
			CEpollSocketWatcher &socket_watcher);

	std::vector<std::string> 	m_bind_ips;
	int 						m_backlog;
	int 						m_port;
	std::set<int> 				m_listen_sockets;
	CThreadPool*					m_thread_pool;
	bool 						m_use_default_tp;
};

#endif /* __EPOLL_SOCKET_H__ */
