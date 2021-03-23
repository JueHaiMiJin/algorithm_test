#include <semaphore.h>
// 需要手动包含信号量头文件
class FooBar
{
private:
    int n;
    //信号量申明
    sem_t fooDone;
    sem_t barDone;

public:
    FooBar(int n)
    {
        this->n = n;
        //初始化信号量
        sem_init(&fooDone, 0, 0);
        //value 初始化为1 是的foo可以先行执行
        sem_init(&barDone, 0, 1);
    }

    void foo(function<void()> printFoo)
    {

        for (int i = 0; i < n; i++)
        {
            sem_wait(&barDone);
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            sem_post(&fooDone);
        }
    }

    void bar(function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {
            sem_wait(&fooDone);
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            sem_post(&barDone);
        }
    }
};

class FooBar
{
private:
    int n;
    mutex mtx;
    condition_variable cv;
    bool fool = false;
public:
    FooBar(int n) : n(n) {}

    void foo(function<void()> printFoo)
    {
        for (int i = 0; i < n; i++)
        {
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck, [&]() { return !fool; });  //当[&]() { return !fool; }返回为true的时候表示成功，程序执行；
            printFoo();
            fool = true;                            //修改条件变量fool使得bar程序可以运行
            cv.notify_all();                        //也可以使用notify_one但是效率不如notify_all
        }
    }

    void bar(function<void()> printBar)
    {
        for (int i = 0; i < n; i++)
        {
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck, [&]() { return fool; });   //当[&]() { return fool; }返回为true的时候表示成功，程序执行；
            printBar();
            fool = false;                           //修改条件变量fool使得foo程序可以运行
            cv.notify_all();                        //也可以使用notify_one但是效率不如notify_all
        }
    }
};