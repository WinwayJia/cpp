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

int32_t BKDRHash(const char * data, int len) {
    uint32_t hash;
    for (int i = 0; i < len; i++) {
        hash += (unsigned char)data[i];
    }
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
    conhash_set_node(&g_nodes[4], "10.1.249.38", 4);
    conhash_set_node(&g_nodes[5], "10.1.249.39", 4);
    //XXX when add new node will change many relations

    size_t str_hash;
    char buff[64];
    int vn = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < g_nodes[i].replicas; j++) {
            vn ++;
        }
        mymap.insert(pair<unsigned int, node_t>(vn, g_nodes[i]));
    }

    for (int i = 0; i < 465; i++) {
        str_hash = BKDRHash(str[i], strlen(str[i]));
        str_hash %= (vn-1);
        it = mymap.lower_bound(str_hash);
        if (it == mymap.end()) {
            it = mymap.begin();
            cout << "not  ";
        }
        cout << str_hash << " --> " << (*it).first << " ------ " << str[i] << " --> " << (*it).second.iden << endl;
    }

    return 0;
}
