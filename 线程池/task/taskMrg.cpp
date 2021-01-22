#include "task.h"


static task_pool* g_task_mrg = NULL;

task_pool *task_pool::GetInstance()
{
    if (g_task_mrg == NULL)
        g_task_mrg = new task_pool;
    return g_task_mrg;
}

task_pool::task_pool(/* args */)
{
}

task_pool::~task_pool()
{
}

//线程池初始化
int task_pool::InitialTaskPool(int num) 
{
    num_threads = num;
    if(num == 0)
        return -1;
    
    //申请线程管理的数组空间
    m_task_mrg = (task_mrg *)new task_mrg[num_threads]();

    //创建工作线程
    for (int i = 0; i < num_threads; i++)
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (!pthread_create(&m_task_mrg[i].p_id, &attr, TaskProcessThread, &m_task_mrg[i]))
            m_task_mrg[i].thread_state = 0;
        pthread_attr_destroy(&attr);
    }

    //常见管理线程
    pthread_t mrg_id;
    pthread_create(&mrg_id, NULL, TaskMrgThread, this);
    return 0;
}

//从任务队列获取一个任务
task_list *task_pool::GetOneTask() 
{
    IntelLock locker(&m_mutex);
    if(m_task_list.size() == 0)
        return NULL;

    task_list *task = m_task_list.front();
    m_task_list.pop_front();
    return task;
}

//添加任务到线程池的任务队列
int task_pool::AddOneTask(task_list *new_task) 
{
    IntelLock locker(&m_mutex);
    m_task_list.push_back(new_task);
    return 0;
}

//获取任务队列
std::list<task_list *>& task_pool::GetTaskList() 
{
    return m_task_list;
}

//获取空闲的线程
task_mrg *task_pool::GetFreeThread() 
{
    for(int i = 0; i < num_threads; i++)
    {
        if(m_task_mrg[i].thread_state == 0)
            return &m_task_mrg[i];
    }

    return NULL;
}

//管理线程
void *task_pool::TaskMrgThread(void *arg) 
{
    while (1)
    {
        task_list *m_task_list = NULL;
        m_task_list = task_pool::GetInstance()->GetOneTask();
        if (!m_task_list)
            sleep(10);

        do
        {
            task_mrg *tmp = task_pool::GetInstance()->GetFreeThread();
            if(m_task_list->data_len < 0)
                break;
            if(tmp && m_task_list->data && m_task_list->data_len > 0)
            {
                tmp->m_task_list.push_back(m_task_list);
            }
            sleep(10);
        } while (1);
    }
}

//工作线程
void *task_pool::TaskProcessThread(void *arg) 
{
    while (1)
    {
        task_list m_task_list;

    }
}