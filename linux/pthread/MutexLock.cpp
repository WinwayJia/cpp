#include <errno.h> 
#include <iostream> 
#include "MutexLock.h"
using namespace std;
#define LOG_TRACE(level,status,function,para) cout << level << " " << status << " " << function << " " << para;

CMutexLock::CMutexLock()
{
    init();
}

int CMutexLock::init()
{
    // 初始化mutex属性
    if (0 != pthread_mutexattr_init(&moMutexAttr))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " init mutex attr failed. errno = "  << errno);
    }
    if (0 != pthread_mutexattr_settype(&moMutexAttr, PTHREAD_MUTEX_RECURSIVE))// | PTHREAD_MUTEX_ERRORCHECK))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " set mutex attr failed. errno = "  << errno);
    }

    if (0 != pthread_mutex_init(&moMutex, &moMutexAttr))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " init mutex failed. errno = "  << errno);
    }
    
}

CMutexLock::~CMutexLock()
{
    if (pthread_mutexattr_destroy(&moMutexAttr))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " set destroy mutex attr failed. errno = "  << errno);
    }
    if (0 != pthread_mutex_destroy(&moMutex))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " destroy mutex failed. errno = "  << errno);
    }
}

int CMutexLock::Lock()
{
    if (0 != pthread_mutex_lock(&moMutex))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " mutex lock failed. errno = "  << errno);
        return errno;
    }
    return 0;
}

int CMutexLock::TryLock()
{
    if (0 != pthread_mutex_trylock(&moMutex))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " mutex try lock failed. errno = "  << errno);
        return errno;
    }
    return 0;
}

int CMutexLock::TimedLock(int aiSecond)
{
    struct timespec loTimeSpec;
    loTimeSpec.tv_sec = aiSecond;
    loTimeSpec.tv_nsec = 0;

    if (0 != pthread_mutex_timedlock(&moMutex, &loTimeSpec))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " mutex timed lock failed. errno = "  << errno);
        return errno;
    }
    return 0;
}

int CMutexLock::Unlock()
{
    if (0 != pthread_mutex_unlock(&moMutex))
    {
        LOG_TRACE(3, false, __FUNCTION__, __LINE__ << " mutex unlock failed. errno = "  << errno);
        return errno;
    }
    return 0;
}


