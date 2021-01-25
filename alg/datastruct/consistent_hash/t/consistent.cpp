#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <functional>
#include <stdint.h> 
#include <stdint.h> 
#include "hosts.h"
using namespace std;

#define NODE_FLAG_INIT  0x01 /* node is initialized */
#define NODE_FLAG_IN    0x02 /* node is added in the server */

typedef unsigned int u_int;

uint32_t GenHash(const char * data, int len);
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
int main (int argc, char** argv)
{
    map<unsigned int, node_t> mymap;
    map<unsigned int, node_t>::iterator it;

    conhash_set_node(&g_nodes[0], "10.1.249.34", 48);
    conhash_set_node(&g_nodes[1], "10.1.249.35", 48);
    conhash_set_node(&g_nodes[2], "10.1.249.36", 48);
    conhash_set_node(&g_nodes[3], "10.1.249.37", 48);
    conhash_set_node(&g_nodes[4], "10.1.249.38", 48);
    conhash_set_node(&g_nodes[5], "10.1.249.39", 48);
    conhash_set_node(&g_nodes[6], "10.1.249.40", 48);
    conhash_set_node(&g_nodes[7], "10.1.249.41", 48);
    conhash_set_node(&g_nodes[8], "10.1.249.42", 48);
    conhash_set_node(&g_nodes[9], "10.1.249.43", 48);

    size_t str_hash;
    char buff[64];
    for (int i = 0; i < 10; i++) {
        for (unsigned j = 0; j < g_nodes[i].replicas; j++) {
            sprintf(buff, "%s-%05d", g_nodes[i].iden, j);
            str_hash  = GenHash(buff, strlen(buff));
//            printf("%s -- %u\n", buff, str_hash);
            mymap.insert(pair<unsigned int, node_t>(str_hash, g_nodes[i]));
        }
    }

    for (unsigned i = 0; i < sizeof(str)/sizeof(str[0]); i++) {
        str_hash = GenHash(str[i], strlen(str[i]));
        it = mymap.lower_bound(str_hash);
        if (it == mymap.end()) {
            it = mymap.begin();
            cout << "not  ";
        }
        cout << str_hash << " --> " << (*it).first << " ------ " << str[i] << " --> " << (*it).second.iden << endl;
    }

    return 0;
}
