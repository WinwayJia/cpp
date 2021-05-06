#ifndef __MUTEX_LOCK_H__
#define __MUTEX_LOCK_H__
#include <pthread.h>

class CMutexLock 
{
public:
    CMutexLock();
    ~CMutexLock();
    int init();
    int Lock();
    int TryLock();
    int TimedLock(int aiSecond);
    int Unlock();
    
private:
    pthread_mutex_t     moMutex;
    pthread_mutexattr_t moMutexAttr;
};

#endif // __MUTEX_LOCK_H__


