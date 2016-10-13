#ifndef __CRITICAL_SECTION_H__
#define __CRITICAL_SECTION_H__

#include <pthread.h>
#include <unistd.h>

class CCriticalSection {
public:
    inline CCriticalSection() {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&mMutex, &attr);
    }

    inline ~CCriticalSection() {
        pthread_mutex_destroy(&mMutex);
    }

    inline void Enter() {
        pthread_mutex_lock(&mMutex);
    }

    inline void Leave() {
        pthread_mutex_unlock(&mMutex);
    }
    ;
private:
    pthread_mutex_t mMutex;

};

class CCriticalSectionHelper {
public:
    inline CCriticalSectionHelper(CCriticalSection& aCriticalSection) :
            moCriticalSection(aCriticalSection) {
        moCriticalSection.Enter();
    }
    inline ~CCriticalSectionHelper() {
        moCriticalSection.Leave();
    }
    inline CCriticalSectionHelper& operator=(const CCriticalSectionHelper& rhs) {
        moCriticalSection = rhs.moCriticalSection;
        return *this;
    }

private:
    CCriticalSection& moCriticalSection;
};

class CCriticalSectionAutoLock {
public:
    inline CCriticalSectionAutoLock(CCriticalSection& aCriticalSection, int aiAuto) :
            moCriticalSection(aCriticalSection), miAutoLock(aiAuto) {
        if (0 != miAutoLock) {
            moCriticalSection.Enter();
        }
    }
    inline ~CCriticalSectionAutoLock() {
        if (0 != miAutoLock) {
            moCriticalSection.Leave();
        }
    }
    inline CCriticalSectionAutoLock& operator=(const CCriticalSectionAutoLock& rhs) {
        moCriticalSection = rhs.moCriticalSection;
        return *this;
    }

private:
    int miAutoLock;
    CCriticalSection& moCriticalSection;
};

#endif // __CRITICAL_SECTION_H__
