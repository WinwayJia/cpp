#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sstream>

#include "http_server.h"
#include "simple_log.h"
#include "simple_parser.h"

CHttpServer::CHttpServer() {
	_port = 3456; // default port
	_backlog = 10;
	_max_events = 1000;
	_pid = 0;
}

int CHttpServer::start(int port, int backlog, int max_events) {
	LOG_WARN(
			"start() method is deprecated, please use start_sync() or start_async() instead!");
	return epoll_socket.start_epoll(port, http_handler, backlog, max_events);
}

void *http_start_routine(void *ptr) {
	CHttpServer *hs = (CHttpServer *) ptr;
	hs->start_sync();
	return nullptr;
}

int CHttpServer::start_async() {
	int ret = pthread_create(&_pid, nullptr, http_start_routine, this);
	if (ret != 0) {
		LOG_ERROR("HttpServer::start_async err:%d", ret);
		return ret;
	}
	return 0;
}

int CHttpServer::join() {
	if (_pid == 0) {
		LOG_ERROR("HttpServer not start async!");
		return -1;
	}
	return pthread_join(_pid, nullptr);
}

int CHttpServer::start_sync() {
	return epoll_socket.start_epoll(_port, http_handler, _backlog, _max_events);
}

void CHttpServer::add_mapping(const std::string& path, method_handler_ptr handler,
		HttpMethod method) {
	http_handler.add_mapping(path, handler, method);
}

void CHttpServer::add_mapping(const std::string& path, json_handler_ptr handler,
		HttpMethod method) {
	http_handler.add_mapping(path, handler, method);
}

void CHttpServer::add_regex_mapping(const std::string& repath,
		json_handler_ptr handler, HttpMethod method) {
	http_handler.add_regex_mapping(repath, handler, method);
}

void CHttpServer::add_bind_ip(const std::string& ip) {
	epoll_socket.add_bind_ip(ip);
}

void CHttpServer::set_thread_pool(CThreadPool *tp) {
	epoll_socket.set_thread_pool(tp);
}

void CHttpServer::set_backlog(int backlog) {
	_backlog = backlog;
}

void CHttpServer::set_max_events(int me) {
	_max_events = me;
}

void CHttpServer::set_port(int port) {
	_port = port;
}

void CHttpEpollWatcher::add_mapping(const std::string& path,
		method_handler_ptr handler, const HttpMethod& method) {
	Resource resource = { method, handler, nullptr };
	resource_map[path] = resource;
}

void CHttpEpollWatcher::add_mapping(const std::string& path,
		json_handler_ptr handler, const HttpMethod& method) {
	Resource resource = { method, nullptr, handler };
	if (1 == method.code) {   // GET
		resource_map[path] = resource;
	} else {
		post_resource_map[path] = resource;
	}
}

void CHttpEpollWatcher::add_regex_mapping(const std::string& repath,
		json_handler_ptr handler, const HttpMethod& method) {
	Resource resource = { method, nullptr, handler };
	try {
		if (1 == method.code) {  // GET
			regex_resource_list.push_back(make_pair(std::regex(repath, std::regex_constants::ECMAScript | std::regex_constants::icase), resource));
		} else if (2 == method.code) {  // POST
			post_regex_resource_list.push_back(make_pair(std::regex(repath, std::regex_constants::ECMAScript | std::regex_constants::icase), resource));
		} else if (3 == method.code) {  // PUT
			put_regex_resource_list.push_back(make_pair(std::regex(repath, std::regex_constants::ECMAScript | std::regex_constants::icase), resource));
		}
	} catch (std::regex_error& e) {
		LOG_ERROR("std::regex failed. %s %s", repath.c_str(), e.what());
	}
}

int CHttpEpollWatcher::handle_request(const CRequest &req, CResponse &res) {
	std::string uri = req.get_request_uri();
	Resource resource;
	bool found = false;
	if (!strncasecmp(req.get_method().c_str(), "GET", 3)) {
		if (this->resource_map.find(uri) == this->resource_map.end()) { // not found, try regex
			for (auto iter = regex_resource_list.begin();
					iter != regex_resource_list.end(); ++iter) {
				if (std::regex_search(uri, iter->first)) {
					found = true;
					resource = iter->second;
				}
			}
			if (!found) {
				res._code_msg = STATUS_NOT_FOUND;
				res._body = STATUS_NOT_FOUND.msg;
				LOG_INFO("page not found which uri:%s", uri.c_str());
				return 0;
			}
		} else {
			resource = this->resource_map[req.get_request_uri()];
		}
	} else if (!strncasecmp(req.get_method().c_str(), "POST", 4)) {
		if (this->post_resource_map.find(uri)
				== this->post_resource_map.end()) { // not found
			res._code_msg = STATUS_NOT_FOUND;
			res._body = STATUS_NOT_FOUND.msg;
			LOG_INFO("page not found which uri:%s", uri.c_str());
			return 0;
		}
		resource = this->post_resource_map[req.get_request_uri()];
	} else if (!strncasecmp(req.get_method().c_str(), "PUT", 3)) {
		if (this->put_resource_map.find(uri)
				== this->put_resource_map.end()) {
			for (auto iter = put_regex_resource_list.begin(); iter != put_regex_resource_list.end(); ++iter) {
				if (std::regex_search(uri, iter->first)) {
					found = true;
					resource = iter->second;
				}
			}
			if (!found) {
				res._code_msg = STATUS_NOT_FOUND;
				res._body = STATUS_NOT_FOUND.msg;
				LOG_INFO("page not found which uri: %s", uri.c_str());
				return 0;
			}
		} else {
			resource = this->put_resource_map[req.get_request_uri()];
		}
	} else {
		// unsupport method
		res._code_msg = STATUS_METHOD_NOT_ALLOWED;
		std::string methods = "GET; POST; PUT";
		res.set_head("Allow", methods);
		res._body.clear();
		LOG_INFO("not allow method, request method:%s = %s", req._line.get_method().c_str(), req.get_method().c_str());
		return 0;
	}

	if (resource.json_ptr != nullptr) {
		Json::Value root;
		resource.json_ptr(req, root);
		res.set_body(root);
	} else if (resource.handler_ptr != nullptr) {
		resource.handler_ptr(req, res);
	}
	LOG_DEBUG("handle response success which code:%d, msg:%s",
			res._code_msg.status_code, res._code_msg.msg.c_str());
	return 0;
}

int CHttpEpollWatcher::on_accept(CEpollContext &epoll_context) {
	int conn_sock = epoll_context.fd;
	epoll_context.ptr = new CHttpContext(conn_sock);
	return 0;
}

int CHttpEpollWatcher::on_readable(int epollfd, epoll_event &event) {
	CEpollContext *epoll_context = (CEpollContext *) event.data.ptr;
	int fd = epoll_context->fd;

	int buffer_size = SS_READ_BUFFER_SIZE;
	char read_buffer[buffer_size];
	memset(read_buffer, 0, buffer_size);

	int read_size = recv(fd, read_buffer, buffer_size, 0);
	if (-1 == read_size && EINTR == errno) {
		return READ_CONTINUE;
	}
	if (-1 == read_size/* io err*/|| 0 == read_size /* close */) {
		return READ_CLOSE;
	}
	LOG_DEBUG("read success which read size:%d", read_size);
	CHttpContext *http_context = (CHttpContext *) epoll_context->ptr;
	if (http_context->get_requset()._parse_part == PARSE_REQ_LINE) {
		http_context->record_start_time();
	}

	int ret = http_context->get_requset().parse_request(read_buffer, read_size);
	if (ret < 0) {
		return READ_CLOSE;
	}
	if (NEED_MORE_STATUS == ret) {
		return READ_CONTINUE;
	}
	if (ret == PARSE_LEN_REQUIRED) {
		http_context->get_res()._code_msg = STATUS_LENGTH_REQUIRED;
		http_context->get_res()._body = STATUS_LENGTH_REQUIRED.msg;
		return READ_OVER;
	}

	this->handle_request(http_context->get_requset(), http_context->get_res());

	return READ_OVER;
}

int CHttpEpollWatcher::on_writeable(CEpollContext &epoll_context) {
	int fd = epoll_context.fd;
	CHttpContext *hc = (CHttpContext *) epoll_context.ptr;
	CResponse &res = hc->get_res();
	bool is_keepalive = (strcasecmp(
			hc->get_requset().get_header("Connection").c_str(), "keep-alive")
			== 0);

	if (!res._is_writed) {
		std::string http_version = hc->get_requset()._line.get_http_version();
		res.gen_response(http_version, is_keepalive);
		res._is_writed = true;
	}

	char buffer[SS_WRITE_BUFFER_SIZE] = {0};
	int read_size = 0;

	// 1. read some response bytes
	int ret = res.readsome(buffer, SS_WRITE_BUFFER_SIZE, read_size);
	// 2. write bytes to socket
	int nwrite = send(fd, buffer, read_size, 0);
	if (nwrite < 0) {
		perror("send fail!");
		return WRITE_CONN_CLOSE;
	}
	// 3. when not write all buffer, we will rollback write index
	if (nwrite < read_size) {
		res.rollback(read_size - nwrite);
	}
	LOG_DEBUG("send complete which write_num:%d, read_size:%d", nwrite,
			read_size);

	if (1 == ret) {/* not send over*/
		LOG_DEBUG(
				"has big response, we will send part first and send other part later ...");
		return WRITE_CONN_CONTINUE;
	}

	if (0 == ret && nwrite == read_size) {
		hc->print_access_log(epoll_context.client_ip);
	}

	if (is_keepalive && nwrite > 0) {
		hc->clear();
		return WRITE_CONN_ALIVE;
	}
	return WRITE_CONN_CLOSE;
}

int CHttpEpollWatcher::on_close(CEpollContext &epoll_context) {
	if (nullptr == epoll_context.ptr) {
		return 0;
	}
	CHttpContext *hc = (CHttpContext *) epoll_context.ptr;
	if (hc != nullptr) {
		delete hc;
		hc = NULL;
	}
	return 0;
}
