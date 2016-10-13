tinyhttp
=============
A tiny http server, based on json protocol. (https://github.com/godlikeJia/tantan)

## feature
* base on epoll
* multi-thread

## depends
 * [jsoncpp](https://github.com/open-source-parsers/jsoncpp) v0.6.0 json serialse
 * [http-parser](https://github.com/nodejs/http-parser) For parse http requset 
 * libpq libpqxx: the c c++ interface for postgresql

## performance
 TODO 

## construct
```
 make && make test && ./output/bin/http_server_test 127.0.0.1 3456
 curl "localhost:3456/hello"
```

## function list
  * http 1.0/1.1(keep-alive support) GET/POST/PUT method
  * data return in Json format

## appendix
 * It's my first time to use PostgreSQL. MySQL is mainly used.
