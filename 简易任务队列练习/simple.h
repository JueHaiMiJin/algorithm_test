#ifndef _SIMPLE_H_
#define _SIMPLE_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct task
{
    int value;
    int m_taskid;
    task{
        value = 0;
        m_taskid = 0
    }
};


class itasklist
{
private:
public:
    itasklist(/* args */);
    ~itasklist();
    virtual void addtask(task &m_task);
    virtual task &gettask();
};

class Taskwork:public itasklist
{
private:
    queue<task> m_tasklist;
public : Taskwork(/* args */);
    ~Taskwork();
    virtual void addtask(task &m_task);
    virtual task &gettask();

    static void* Inserttask(void* arg);
};

class process
{
public:
    process(/* args */);
    ~process();
    void taskprocess(task &m_task);

    static void* Gettask(void* arg);
};




#endif