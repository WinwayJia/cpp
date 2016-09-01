#include "hash_nodes.h"

uint32_t get_hash_value(const void* key, int len) {
    uint32_t seed = 5381;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t h = seed ^ len;

    const unsigned char *data = (const unsigned char *)key;

    while(len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch(len) {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0]; h *= m;
    };

    /* Do a few final mixes of the hash to ensure the last few
     * bytes are well-incorporated. */
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int)h;
}

hash_nodes::hash_nodes(hash_func func) : m_hash_func(func) {}
hash_nodes::~hash_nodes() {}

void hash_nodes::add_host(host_t *n) {
    char buf[32];
    uint32_t val;

    m_hosts.push_back(*n);
    host_t &h = m_hosts.back();
    string hash_str = h.ipaddr;

    for (int i = 0; i < h.replicas; i++) {
        sprintf(buf, "-%03d", i);
        hash_str += buf;
        val = m_hash_func((void*)hash_str.c_str(), (int)hash_str.size());
        m_nodes.insert(pair<uint32_t, host_t*>(val, &h));
    }
}

void hash_nodes::del_host(host_t *n) {
}

const host_t& hash_nodes::get_host(const string & str) {
    map<uint32_t, host_t*>::const_iterator it;
    uint32_t val;

    val = m_hash_func((void*)str.c_str(), (int)str.size());
    it = m_nodes.lower_bound(val);
    if (it == m_nodes.end()) {
        it = m_nodes.begin();
        cout << "not  ";
    } 

    return *it->second;
}

void hash_nodes::traverse() {
    map<uint32_t, host_t*>::const_iterator it;
    for (it = m_nodes.begin(); it != m_nodes.end(); it++) {
        cout << it->second/*->ipaddr*/ << " --> " << it->first << endl;
    }

    vector<host_t>::const_iterator vi;
    for (vi = m_hosts.begin(); vi != m_hosts.end(); vi++) {
        const host_t &h = static_cast<host_t>(*vi);
        cout << &h << endl;
    }
}


int main(int argc, char** argv) {
    host_t n;
    hash_nodes ch;

    set_host(n, "10.1.249.34", 1);
    ch.add_host(&n);

    set_host(n, "10.1.249.33", 1);
    ch.add_host(&n);

    set_host(n, "10.1.249.32", 1);
    ch.add_host(&n);

    ch.traverse();

    host_t node = ch.get_host("Hello");

    cout << node.ipaddr << endl;

    return 0;
}
