#include <iostream>
#include <pthread.h>
#include <Windows.h>

class task_mutex
{
private:
    pthread_mutex_t mutex;
    unsigned int current_threadid;

public:
    task_mutex();
    ~task_mutex();
    bool lock();
    bool unlock();
    bool sharelock();
    bool unlockshare();

};


enum LOCKSTYLE
{
    MUTEX_LOCK,
    SHARE_LOCK,
    TRY_LOCK
};

class IntelLock
{
private:
    int lock_style;
    task_mutex*  m_mutex;

public :
    IntelLock(task_mutex *pmutex, int nlockstyle = MUTEX_LOCK);
    ~IntelLock();
};





