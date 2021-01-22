// 桥接模式

#include <iostream>
using namespace std;

class software
{
private:
    /* data */
public:
    software(/* args */);
    ~software();
    virtual void run() { cout << "this is a software \n"; }
};

class gamesoftware : public software
{
public:
    gamesoftware();
    ~gamesoftware();
    virtual void run() { cout << "Game software \n"; }
};

class mediasoftware : public software
{
public:
    mediasoftware();
    ~mediasoftware();
    virtual void run() { cout << "Media software \n"; }
};

class Brand : public software
{
protected:
    software* m_software;
public:
    Brand(/* args */);
    ~Brand();
    void setsoftware(software* in_software) { m_software = in_software; }
    virtual void run();
};

class HuaweiBrand : public Brand
{
private:
    /* data */
public:
    HuaweiBrand(/* args */);
    ~HuaweiBrand();
    void run() { m_software->run(); }
};

class XiaomiBrand : public Brand
{
private:
    /* data */
public:
    XiaomiBrand(/* args */);
    ~XiaomiBrand();
    void run() { m_software->run(); }
};

int main(int argc, char const *argv[])
{
    Brand* brand = new HuaweiBrand();
    
    brand->setsoftware(new gamesoftware());
    brand->run();

    brand->setsoftware(new mediasoftware());
    brand->run();

    return 0;
}
