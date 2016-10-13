// $_FILEHEADER_BEGIN ***************************
// 版权声明: 北京畅聊天下科技公司版权所有
//			Copyright (C) 2015-  ChangLiaoTianXia Corporation. All Rights
// 文件名称: MutexLock.h
// 创建日期: 2015/09/22
// 创 建 人: jiawenhui
// 文件说明： 线程同步--互斥量
// 原   因:  创建文件
// $_FILEHEADER_END *****************************
 
 

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


