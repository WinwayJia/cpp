#ifndef __SIMPLE_PARSER_H__
#define __SIMPLE_PARSER_H__

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <sys/time.h>

#include "json/json.h"
#include "simple_log.h"
#include "http_parser.h"

struct CodeMsg {
	int status_code;
	std::string msg;
};

const static CodeMsg STATUS_OK = { 200, "OK" };
const static CodeMsg STATUS_NOT_FOUND = { 404, "Not Found" };
const static CodeMsg STATUS_METHOD_NOT_ALLOWED = { 405, "Method Not Allowed" };
const static CodeMsg STATUS_LENGTH_REQUIRED = { 411, "Length Required" };

const static int PARSE_REQ_LINE = 0;
const static int PARSE_REQ_HEAD = 1;
const static int PARSE_REQ_BODY = 2;
const static int PARSE_REQ_OVER = 3;
const static int PARSE_REQ_HEAD_OVER = 4;

const static int NEED_MORE_STATUS = 1;
const static int PARSE_LEN_REQUIRED = 2;

class CRequestParam {
public:
	std::string get_param(const std::string &name) const;

	void get_params(const std::string &name, std::vector<std::string> &params) const;

	/**
	 * query_url : name=tom&age=3
	 */
	int parse_query_url(std::string &query_url);
private:
//	std::multimap<std::string, std::string> _params;
    Json::Value _params;
};

class CRequestLine {
public:
	std::string get_request_uri() const;

	const CRequestParam &get_request_param() const;

	std::string to_string();
	/**
	 * request_url : /sayhello?name=tom&age=3
	 */
	int parse_request_url_params();

	std::string get_method() const;

	void set_method(const std::string& m);

	std::string get_request_url() const;

	void set_request_url(const std::string& url);

	void append_request_url(const std::string& p_url);

	std::string get_http_version();

	void set_http_version(const std::string& v);
private:
	CRequestParam _param;
	std::string _method;       // like GET/POST
	std::string _request_url;  // like /hello?name=aaa
	std::string _http_version; // like HTTP/1.1
};

class CRequestBody {
public:
	std::string get_param(const std::string& name) const;

	void get_params(std::string &name, std::vector<std::string> &params);

	std::string *get_raw_string();

	CRequestParam *get_req_params();
private:
	std::string _raw_string;
	CRequestParam _req_params;
};

class CRequest {
public:
	CRequest();

	~CRequest();

	std::string get_param(const std::string& name) const;

	std::string get_unescape_param(const std::string& name) const;

	void get_params(std::string &name, std::vector<std::string> &params);

	void add_header(std::string &name, std::string &value);

	std::string get_header(const std::string& name);

	std::string get_request_uri() const;

	int parse_request(const char *read_buffer, int read_size);

	int clear();

	CRequestBody *get_body();

	std::string get_method() const;

	bool _last_was_value;
	std::vector<std::string> _header_fields;
	std::vector<std::string> _header_values;
	int _parse_part;
	int _parse_err;
	CRequestLine _line;
private:
	std::map<std::string, std::string> _headers;
	int _total_req_size;
	CRequestBody _body;
	http_parser_settings _settings;
	http_parser _parser;

};

class CResponse {
public:
	CResponse(CodeMsg status_code = STATUS_OK);
	CResponse(CodeMsg status_code, Json::Value &body);

	void set_head(std::string name, std::string &value);

	void set_body(Json::Value &body);

	int gen_response(std::string &http_version, bool is_keepalive);

	/**
	 * return 0: read part, 1: read over, -1:read error
	 */
	int readsome(char *buffer, int buffer_size, int &read_size);

	/**
	 * rollback num bytes in response bytes
	 */
	int rollback(int num);

	bool _is_writed;
	CodeMsg _code_msg;
	std::string _body;
private:
	std::map<std::string, std::string> _headers;
	std::stringstream _res_bytes;
};

class CHttpContext {
public:
	CHttpContext(int fd);

	~CHttpContext();

	int record_start_time();

	int get_cost_time();

	void print_access_log(std::string &client_ip);

	inline void delete_req_res();

	void clear();

	CResponse &get_res();

	CRequest &get_requset();

	int _fd;
	timeval _start;
private:
	CResponse *_res;
	CRequest *_req;
};

#endif /* __SIMPLE_PARSER_H__ */
