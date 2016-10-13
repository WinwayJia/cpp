#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>
#include <deque>
#include <vector>

const int DEF_STARTED = 0;
const int DEF_STOPPED = 1;

class CMutex {
public:
	CMutex() {
		pthread_mutex_init(&m_lock, NULL);
		is_locked = false;
	}
	~CMutex() {
		while (is_locked)
			;
		unlock(); // Unlock Mutex after shared resource is safe
		pthread_mutex_destroy(&m_lock);
	}
	void lock() {
		pthread_mutex_lock(&m_lock);
		is_locked = true;
	}
	void unlock() {
		is_locked = false; // do it BEFORE unlocking to avoid race condition
		pthread_mutex_unlock(&m_lock);
	}
	pthread_mutex_t* get_mutex_ptr() {
		return &m_lock;
	}
private:
	pthread_mutex_t m_lock;
	volatile bool is_locked;
};

class CCondVar {
public:
	CCondVar() {
		pthread_cond_init(&m_cond_var, NULL);
	}
	~CCondVar() {
		pthread_cond_destroy(&m_cond_var);
	}
	void wait(pthread_mutex_t* mutex) {
		pthread_cond_wait(&m_cond_var, mutex);
	}
	void signal() {
		pthread_cond_signal(&m_cond_var);
	}
	void broadcast() {
		pthread_cond_broadcast(&m_cond_var);
	}
private:
	pthread_cond_t m_cond_var;
};

typedef void* (*thread_fun)(void*);
class CTask {
public:
	CTask(thread_fun func, void* arg); // pass a free function pointer
	virtual ~CTask();
	void run();
private:
	thread_fun m_fn_ptr;
	void* m_arg;
};

typedef void (*thread_start_callback)();

class CThreadPool {
public:
	CThreadPool();
	virtual ~CThreadPool();
	int start();
	int destroy_threadpool();
	void* execute_thread();
	int add_task(CTask* task);
	void set_thread_start_cb(thread_start_callback f);
	void set_task_size_limit(int size);
	void set_pool_size(int pool_size);
	thread_start_callback m_scb;
private:
	int m_pool_size;
	CMutex m_task_mutex;
	CCondVar m_task_cond_var;
	std::vector<pthread_t> m_threads; // storage for threads
	std::deque<CTask*> m_tasks;
	volatile int m_pool_state;
	int m_task_size_limit;
};

#endif /* __THREAD_POOL_H__ */
