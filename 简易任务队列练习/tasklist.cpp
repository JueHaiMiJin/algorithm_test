#include "simple.h"

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

void *Taskwork::Inserttask(void *arg)
{
    sleep(1);
    int count = 0;
    Taskwork* tmp = (Taskwork*)arg;
    while (1)
    {
        task tmp_task = {rand()%199, ++cout};
        tmp->addtask(tmp_task);
        sleep(1);
    }
}

void process::taskprocess(task &m_task)
{
    cout << "taskid: " << m_task.m_taskid << " value: " << m_task.value << endl;
}

void *process::Gettask(void *arg)
{
    process* tmp = (process*)arg;
    
}