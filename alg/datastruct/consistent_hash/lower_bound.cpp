#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <functional>
#include <stdint.h> 
#include <stdint.h> 
#include "t.h"
using namespace std;

#define NODE_FLAG_INIT  0x01 /* node is initialized */
#define NODE_FLAG_IN    0x02 /* node is added in the server */

typedef unsigned int u_int;


#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
    || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
        +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

uint32_t BKDRHash(const char * data, int len) {
    uint32_t hash = len, tmp;
    int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}
/* nodes structure */
typedef struct node_s
{
    char iden[64]; /* node name or some thing identifies the node */
    u_int replicas; /* number of replica virtual nodes */
    u_int flag;
} node_t;

void conhash_set_node(struct node_s *node, const char *iden, u_int replica)
{
    strncpy(node->iden, iden, sizeof(node->iden)-1);
    node->replicas = replica;
    node->flag = NODE_FLAG_INIT;
}

struct node_s g_nodes[64];
int main ()
{
    map<unsigned int, node_t> mymap;
    map<unsigned int, node_t>::iterator it;

    conhash_set_node(&g_nodes[0], "10.1.249.34", 4);
    conhash_set_node(&g_nodes[1], "10.1.249.35", 4);
    conhash_set_node(&g_nodes[2], "10.1.249.36", 4);
    conhash_set_node(&g_nodes[3], "10.1.249.37", 4);
    //conhash_set_node(&g_nodes[4], "10.1.249.38", 4);
    conhash_set_node(&g_nodes[5], "10.1.249.39", 4);

    size_t str_hash;
    char buff[64];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < g_nodes[i].replicas; j++) {
            sprintf(buff, "%s-%03d", g_nodes[i].iden, j);
            str_hash  = BKDRHash(buff, strlen(buff));
            printf("%s -- %u\n", buff, str_hash);
            mymap.insert(pair<unsigned int, node_t>(str_hash, g_nodes[i]));
        }
    }

    for (int i = 0; i < 32; i++) {
        str_hash = BKDRHash(str[i], strlen(str[i]));
        it = mymap.lower_bound(str_hash);
        if (it == mymap.end()) {
            it = mymap.begin();
            cout << "not  ";
        }
        cout << str_hash << " --> " << (*it).first << " ------ " << str[i] << " --> " << (*it).second.iden << endl;
    }

    return 0;
}
