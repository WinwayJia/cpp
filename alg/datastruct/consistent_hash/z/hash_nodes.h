#ifndef __HASH_NODES_H__
#define __HASH_NODES_H__
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <sys/time.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#define set_host(node, addr, rep)    \
    do {                             \
        node.ipaddr = addr;          \
        node.replicas = rep;         \
    } while(0)

typedef uint32_t (*hash_func)(const void*, int);
uint32_t get_hash_value(const void*, int);

typedef struct host_s {
    string ipaddr;
    int    replicas;

} host_t;

class hash_nodes {
    public:
        hash_nodes(hash_func func=get_hash_value);
        ~hash_nodes();

        void add_host(host_t *n);
        void del_host(host_t *n); 
        const host_t& get_host(const string & str);

        void traverse();

    private:
        hash_func                       m_hash_func;
        map<uint32_t, host_t*>          m_nodes;
        vector<host_t>                  m_hosts;
};

#endif
