#include "simple.h"

Taskwork::Taskwork(/* args */)
{
    pthread_mutex_init(&m_mutex, PTHREAD_MUTEX_INITIALIZER);

}

void Taskwork::addtask(task &m_task)
{
    m_tasklist.push(m_task);
}

task &Taskwork::gettask()
{
    task task_ret = m_tasklist.front();
    m_tasklist.pop();
    return task_ret;
}

int Taskwork::getlistsize()
{
    return m_tasklist.size();
}

void process::taskprocess(task &m_task)
{
    cout << "taskid: " << m_task.m_taskid << " value: " << m_task.value << endl;
}

void *Inserttask(void *arg)
{
    sleep(1);
    int count = 0;
    Taskwork *tmp = (Taskwork *)arg;
    while (1)
    {
        task tmp_task = {rand() % 199, ++cout};
        //上锁
        pthread_mutex_lock(&tmp->m_mutex);
        tmp->addtask(tmp_task);
        //解锁
        pthread_mutex_unlock(&tmp->m_mutex);
        sleep(1);
    }
}

void *Gettask(void* arg)
{
    Taskwork *tmp = (Taskwork *)arg;
    while (1)
    {
        if (tmp->getlistsize())
        {
            //上锁
            pthread_mutex_lock(&tmp->m_mutex);
            task tmp_task = tmp->gettask();
            //解锁
            pthread_mutex_unlock(&tmp->m_mutex);
        }
        else
        {
            /* code */
        } 
    }
}