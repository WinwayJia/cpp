#include <stdexcept>
#include <exception>
#include <stdio.h>
#include "connection_pool.h"

CConnPool *CConnPool::m_conn_pool = NULL;

CConnPool::CConnPool(const std::string& IP, unsigned short port, const std::string& userName,
		const std::string& password, const std::string& db_name, int max_size) : m_ip(IP), m_port(port), m_user_name(userName),
				m_password(password), m_db_name(db_name), m_max_size(max_size) {

    this->InitConnection(m_max_size / 2);
}

// connection pool
CConnPool*CConnPool::GetInstance() {
    if (m_conn_pool == NULL) {
        m_conn_pool = new CConnPool("192.168.20.128", 5432, "db_user", "111111", "db_user_info", 50);
    }
    return m_conn_pool;
}

void CConnPool::InitConnection(int iInitialSize) {
    pqxx::connection* conn;

    CCriticalSectionHelper loGuard(m_lock);
    for (int i = 0; i < iInitialSize; i++) {
        conn = this->CreateConnection();
        if (conn) {
            m_conn_list.push_back(conn);
            ++(this->m_curr_size);
        } else {
            perror("create CONNECTION failed");
        }
    }
}

pqxx::connection* CConnPool::CreateConnection() {
	pqxx::connection * conn = NULL;
	std::string conn_info = "dbname=" + m_db_name + " user=" + m_user_name + " password="+
			m_password + " hostaddr=" + m_ip + " port=" + std::to_string(m_port);
	try {
		conn = new pqxx::connection(conn_info);
		return conn;
	} catch (...) {
		LOG_ERROR("connect to postgresql failed. info=%s", conn_info.c_str());
		return NULL;
	}
}

// fetch a connection from pool
pqxx::connection* CConnPool::GetConnection() {
    pqxx::connection* conn = NULL;
    CCriticalSectionHelper loGurad(m_lock);

    if (m_conn_list.size() > 0) {
        conn = m_conn_list.front();
        m_conn_list.pop_front();
        if (!conn->is_open()) {
            delete conn;
            conn = this->CreateConnection();
        }

        if (conn == NULL) {
            --m_curr_size;
        }
        return conn;
    } else {
        if (m_curr_size < m_max_size) {
            conn = this->CreateConnection();
            if (conn) {
                ++m_curr_size;
                return conn;
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    }
}

void CConnPool::ReleaseConnection(pqxx::connection * conn) {
    if (conn) {
    	CCriticalSectionHelper loGuard(m_lock);
        m_conn_list.push_back(conn);
    }
}

CConnPool::~CConnPool() {
    this->DestoryConnPool();
}

void CConnPool::DestoryConnPool() {
    CCriticalSectionHelper loGuard(m_lock);
    for (auto icon = m_conn_list.begin(); icon != m_conn_list.end(); ++icon) {
        this->DestoryConnection(*icon);
    }
    m_curr_size = 0;
    m_conn_list.clear();
}

void CConnPool::DestoryConnection(pqxx::connection* conn) {
    if (conn) {
        try {
            conn->disconnect();
        } catch (...) {
           LOG_ERROR("close postgresql connection failed.");
        }
        delete conn;
    }
}
