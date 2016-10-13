#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "simple_log.h"
#include "../src/thread_pool.h"
#include "../src/http_server.h"
#include "../src/connection_pool.h"
#include "../deps/json-cpp/include/json/json.h"

pthread_key_t g_tp_key;
CConnPool* g_conn_poll = NULL;

void get_users(const CRequest &request, Json::Value &root) {
	pqxx::connection* conn = g_conn_poll->GetConnection();
	if (nullptr == conn) {
	    LOG_ERROR("get postgresql connection failed.");
	    return ;
	}

	pqxx::work w(*conn);
	Json::Value value;
	pqxx::result r = w.exec("select id, name, type from t_user_info");
	for (auto row=r.begin(); row != r.end(); ++row) {
		value["id"] = row[0].c_str();
		value["name"] = row[1].c_str();
		value["type"] = row[2].c_str();
		LOG_INFO("%s %s %s", row[0].c_str(), row[1].c_str(), row[2].c_str());
		root.append(value);
	}
}

void post_user(const CRequest &request, Json::Value &root) {
	std::string name = request.get_param("name");

    pqxx::connection* conn = g_conn_poll->GetConnection();
    if (nullptr == conn) {
        LOG_ERROR("get postgresql connection failed.");
        return ;
    }
    pqxx::work w(*conn);
    char sql[128] = {0};
    snprintf(sql, 128, "select * from pr_add_new_user('%s', 'user');", name.c_str());

    pqxx::result r = w.exec(sql);

    w.commit();

	LOG_DEBUG("register user which name:%s", name.c_str());
    root["id"] = r[0][0].c_str();
	root["name"] = name;
	root["type"] = "user";
}


void get_relationship(const CRequest &request, Json::Value &root) {
	std::string name = request.get_param("name");
	std::string age = request.get_param("age");

	pqxx::connection* conn = g_conn_poll->GetConnection();
	if (nullptr == conn) {

	}

	pqxx::work w(*conn);
	Json::Value value;
	pqxx::result r = w.exec("select id, name, type from t_user_info");
	for (auto row=r.begin(); row != r.end(); ++row) {
		value["id"] = row[0].c_str();
		value["name"] = row[1].c_str();
		value["type"] = row[2].c_str();
		LOG_INFO("%s %s %s", row[0].c_str(), row[1].c_str(), row[2].c_str());
		root.append(value);
	}
}

void put_relationship(const CRequest &request, Json::Value &root) {
    std::string state = request.get_param("state");

	root["state"] = state;
	root["msg"] = "login success!";
}

int main(int argc, char **args) {
    int ret = log_init("./conf", "simple_log.conf");
    if (ret != 0) {
        printf("log init error!");
        return 0;
    }
    if (argc < 3) {
        LOG_ERROR("usage: ./http_server_test [bind ip] [port]");
        return -1;
    }

    CThreadPool tp;
    tp.set_pool_size(16);

    g_conn_poll = CConnPool::GetInstance();

    CHttpServer http_server;
    http_server.set_thread_pool(&tp);

    std::string uri_users = "/users";
    std::string uri_relationship = "/users/[0-9]+/relationships";
    http_server.add_mapping(uri_users, get_users);
    http_server.add_mapping(uri_users, post_user, POST_METHOD);
    http_server.add_regex_mapping(uri_relationship, get_relationship);
    http_server.add_regex_mapping(uri_relationship, put_relationship, PUT_METHOD);

    http_server.add_bind_ip(args[1]);
    http_server.set_port(atoi(args[2]));
    http_server.set_backlog(100000);
    http_server.set_max_events(100000);
    http_server.start_async();
    http_server.join();
    return 0;
}
