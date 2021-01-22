#include <iostream>
using namespace std;

//饿汉模式，申明变量时初始化

//下面的写法有问题，对线程来说并不安全，而且不是全局唯一，不能算是单例模式
class Ehmode
{
private:
    Ehmode();
    ~Ehmode();
    Ehmode *m_eh = new Ehmode();
public:
    Ehmode *GetInstence()
    {
        return m_eh;
    }
};

//修改 全局唯一的m_eh变量
class Ehmode
{
private:
    Ehmode();
    ~Ehmode();
    static Ehmode *m_eh;

public:
    static Ehmode *GetInstence()
    {
        return m_eh;
    }
};

//初始化static 
Ehmode *Ehmode::m_eh = new Ehmode();


// 懒汉式
// 懒汉式：先声明一个空变量，需要用时才初始化。
class Lhmode
{
private:
    static Lhmode* m_lh;
    Lhmode();
    ~Lhmode();
public:
    static Lhmode* GetInstance()
    {
        if (m_lh == NULL) //判断是否未初始化
        {
            //加锁 保证多线程安全
            if (m_lh == NULL) //防止在加锁过程中已经被初始化，再次进行判断确保线程安全
                m_lh = new Lhmode();
            //解锁
        }
        return m_lh;
    }
};
//static 变量初始化
Lhmode *Lhmode::m_lh = NULL;
