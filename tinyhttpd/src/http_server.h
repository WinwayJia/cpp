#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include <string>
#include <map>
#include <regex>
#include <list>
#include <sys/epoll.h>

#include "epoll_socket.h"
#include "json/json.h"
#include "simple_parser.h"

struct HttpMethod {
	int code;
	std::string name;
};

const static HttpMethod GET_METHOD = { 1, "GET" };
const static HttpMethod POST_METHOD = { 2, "POST" };
const static HttpMethod PUT_METHOD = {3, "PUT" };

typedef void (*method_handler_ptr)(const CRequest& request, CResponse &response);
typedef void (*json_handler_ptr)(const CRequest& request, Json::Value &response);

struct Resource {
	HttpMethod method;
	method_handler_ptr handler_ptr;
	json_handler_ptr json_ptr;
};

class CHttpEpollWatcher : public CEpollSocketWatcher {
public:
	virtual ~CHttpEpollWatcher() {
	}

	void add_mapping(const std::string& path, method_handler_ptr handler,
			const HttpMethod& method = GET_METHOD);

	void add_mapping(const std::string& path, json_handler_ptr handler,
			const HttpMethod& method = GET_METHOD);

	void add_regex_mapping(const std::string& repath, json_handler_ptr handler,
			const HttpMethod& method = GET_METHOD);

	int handle_request(const CRequest &request, CResponse &response);

	virtual int on_accept(CEpollContext &epoll_context) override;

	virtual int on_readable(int epollfd, epoll_event &event) override;

	virtual int on_writeable(CEpollContext &epoll_context) override;

	virtual int on_close(CEpollContext &epoll_context) override;
private:
	std::map<std::string, Resource> resource_map;
	std::map<std::string, Resource> post_resource_map;
	std::map<std::string, Resource> put_resource_map;
	std::list<std::pair<std::regex, Resource>> regex_resource_list;
	std::list<std::pair<std::regex, Resource>> post_regex_resource_list;
	std::list<std::pair<std::regex, Resource>> put_regex_resource_list;
};

class CHttpServer {
public:
	CHttpServer();

	void add_mapping(const std::string& path, method_handler_ptr handler,
			HttpMethod method = GET_METHOD);

	void add_mapping(const std::string& path, json_handler_ptr handler,
			HttpMethod method = GET_METHOD);

	void add_regex_mapping(const std::string& repath, json_handler_ptr handler,
			HttpMethod method = GET_METHOD);

	void add_bind_ip(const std::string& ip);

	int start(int port, int backlog = 10, int max_events = 1000);

	int start_async();

	int join();

	int start_sync();

	void set_thread_pool(CThreadPool *tp);

	void set_backlog(int backlog);

	void set_max_events(int me);

	void set_port(int port);
private:
	CHttpEpollWatcher http_handler;
	CEpollSocket epoll_socket;
	int _backlog;
	int _max_events;
	int _port;
	pthread_t _pid; // when start async
};

#endif /* __HTTP_SERVER_H__ */
