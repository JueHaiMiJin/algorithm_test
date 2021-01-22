#ifndef _TASK_H
#define _TASK_H

#include <iostream>
#include <list>
#include <pthread.h>
#include "mutex.h"

//工作线程的回调函数
typedef void (*callback)(void* data, int data_len);

//工作线程结构体
typedef struct taskList
{
    taskList()
    {
        m_work = NULL;
        data = NULL;
        data_len = 0;
    };

    callback *m_work;
    char* data;
    int data_len;

}task_list;




//管理线程结构体
typedef struct taskMrg
{
    taskMrg(){
        thread_state                = 0;
        cond                        = PTHREAD_COND_INITIALIZER;
        p_id                        = 0;

    };
    int                             thread_state;                               //0 空闲 1 busy
    pthread_cond_t                  cond;
    pthread_t                       p_id;
    std::list<task_list*>           m_task_list;
}task_mrg;


//线程池
class task_pool
{
private:
    int num_threads;                                //线程池中的线程数目
    task_mrg *m_task_mrg;                           //线程管理结构数组
    task_mutex m_mutex;                             //互斥锁
    std::list<task_list *> m_task_list;             //任务队列

public:
    static task_pool* GetInstance();
    task_pool();                                    //构造函数
    ~task_pool();                                   //析构函数
    int InitialTaskPool(int num);                   //线程池初始化

    task_list *GetOneTask();                        //从任务队列获取一个任务
    int AddOneTask(task_list *new_task);            //添加任务到线程池的任务队列

    std::list<task_list *> &GetTaskList();          //获取任务队列
    task_mrg *GetFreeThread();                      //获取空闲的线程

    static void *TaskMrgThread(void *arg);          //管理线程
    static void *TaskProcessThread(void *arg);      //工作线程
};

#endif