#include <iostream>
#include <string>
#include <vector>
#include <pthread>
#include <pthread.h>
#include <unistd.h>


using namespace std;

struct task
{
    int value;
    struct task* next; 
};

class tasklist
{
private:
    task *m_task_list_head;
    task *m_task_list_real;
    int m_task_num;
    pthread_mutex_t m_mutex;

public :
    tasklist()
    {
        m_task_list_head =  NULL;
        m_task_list_real = m_task_list_head;
        m_task_num = 0;
        pthread_mutex_init(&m_mutex, PTHREAD_MUTEX_INITIALIZER);
    }

    ~tasklist()
    {
        task *p = m_task_list_head;
        for (; p != NULL; p++)
        {
            if(p != NULL)
                free(p);
        }
    }

    void insertTask(task *in_task)
    {
        if(in_task == NULL)
            return;
        pthread_mutex_lock(&m_mutex);
        if (m_task_list_head == NULL)
            m_task_list_head = in_task;
        else
        {
            m_task_list_real->next = in_task;
            m_task_list_real = in_task;
        }
        m_task_num++;
        cout << "m_task_num: " << m_task_num << endl;
        pthread_mutex_unlock(&m_mutex);
    }

    void PopTask()
    {
        pthread_mutex_lock(&m_mutex);
        if (m_task_num == 0)
        {
            pthread_mutex_unlock(&m_mutex);
            return NULL;
        }
        else
        {
            task* ret = m_task_list_head;
            m_task_list_head = m_task_list_head->next;
            m_task_num --;
            pthread_mutex_unlock(&m_mutex);
            return ret;
        }
    }
};

void* theadinserttask(void* arg)
{
    tasklist* m_tasklist = (tasklist*) arg;
    while(1)
    {
        task *tmp = (task *)malloc(sizeof(task));
        tmp->value = rand() % 1900 + 1;
        m_tasklist->insertTask(tmp);
        sleep(5);
    }
}

int main(int argc, char const *argv[])
{
    tasklist* m_tasklist = new tasklist();
    pthread_t pid;
    pthread_create(&pid, NULL, theadinserttask, (void *)m_tasklist);
    return 0;
}

