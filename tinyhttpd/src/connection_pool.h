#ifndef __CONNECTION_POOL_H__
#define __CONNECTION_POOL_H__


#include <list>
#include <string>
#include <pqxx/pqxx>
#include "critical_section.h"
#include "simple_log.h"
#undef _MSC_VER
class CConnPool {
    public:
        virtual ~CConnPool();
        pqxx::connection* GetConnection();     // get a connection
        void ReleaseConnection(pqxx::connection *conn); // release connection, back to pool
        static CConnPool *GetInstance(); // get an instance

    private:
        int m_curr_size = 0; // current connection number
        int m_max_size = 0; // max connection number
        std::string m_user_name;
        std::string m_password;
        std::string m_ip;
        unsigned short m_port;
        std::string m_db_name;
        std::list<pqxx::connection*> m_conn_list;
        CCriticalSection m_lock;
        static CConnPool *m_conn_pool;

        pqxx::connection* CreateConnection();
        void InitConnection(int iInitialSize); 
        void DestoryConnection(pqxx::connection *conn);
        void DestoryConnPool(); 
        CConnPool(const std::string& IP, unsigned short port, const std::string& userName,
        		const std::string& password, const std::string& db_name, int max_size);
};
#endif  // __CONNECTION_POOL_H__
