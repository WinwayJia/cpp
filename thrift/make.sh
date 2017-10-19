
g++ -ggdb3 -std=c++11 -o first_client first_client.cpp first.cpp first_types.cpp /usr/local/lib//libthrift.a -lpthread

g++ -ggdb3 -std=c++11 -o first_server first_server.cpp first.cpp first_types.cpp /usr/local/lib/libthrift.a  -lpthread
