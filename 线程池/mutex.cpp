#include "mutex.h"

task_mutex::task_mutex()
{
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    int ret = pthread_mutex_init(&mutex, &mutex_attr);
    if(ret != 0)
    {
        printf("mutex create failed \n");
    }
    pthread_mutexattr_destroy(&mutex_attr);

    current_threadid = 0;

}

task_mutex::~task_mutex()
{
    pthread_mutex_destroy(&mutex);
}

bool task_mutex::lock()
{
    current_threadid = GetCurrentThreadId();
    pthread_mutex_lock(&mutex);
    return true;
}

bool task_mutex::unlock()
{
    pthread_mutex_unlock(&mutex);
    return true;
}


bool task_mutex::sharelock()
{
    current_threadid = GetCurrentThreadId();
    pthread_mutex_lock(&mutex);
}


bool task_mutex::unlockshare()
{
    pthread_mutex_unlock(&mutex);
    return true;
}

IntelLock::IntelLock(task_mutex *pmutex, int nlockstyle = MUTEX_LOCK)
{
    lock_style = nlockstyle;
    m_mutex = pmutex;

    if(m_mutex == NULL)
        return;
    
    switch (lock_style)
    {
    case MUTEX_LOCK:
        m_mutex->lock(); 
        break;
    case SHARE_LOCK:
        m_mutex->sharelock();
        break;
    default:
        m_mutex->lock();
        break;
    }
}

IntelLock::~IntelLock()
{
    if(m_mutex == NULL)
        return;
    
    switch (lock_style)
    {
    case MUTEX_LOCK:
        m_mutex->unlock();
        break;
    case SHARE_LOCK:
        m_mutex->unlock();
        break; 
    default:
        break;
    }
}