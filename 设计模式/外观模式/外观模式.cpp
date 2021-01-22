#include <iostream>

using namespace std;

class Browser
{
public:
    Browser();
    ~Browser();
    void open();
    void close();
};

class Weixin
{
public:
    Weixin();
    ~Weixin();
    void open();
    void close();
};

class QQ
{
public:
    QQ();
    ~QQ();
    void open();
    void close();
};


//外观模式是将一些一起使用的接口并入一个类中
class Interface
{
private:
    Browser m_broswer;
    Weixin m_weixin;
    QQ  m_qq;

public: 
    Interface();
    ~Interface();
    void open()
    {
        m_broswer.open();
        m_weixin.open();
        m_qq.open();
    }
    void close(){
        m_broswer.close();
        m_weixin.close();
        m_qq.close();
    }
};