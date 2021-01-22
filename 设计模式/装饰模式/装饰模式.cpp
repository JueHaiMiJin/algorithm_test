#include <iostream>
#include <string>

using namespace std;

//抽象房子类
class IsHouse
{
private:
    /* data */
public:
    IsHouse(/* args */);
    ~IsHouse();
    virtual void live();
};

//具体的房子的类
class House : public IsHouse
{
public:
    House();
    ~House();
    void live() { cout << "House for live " << endl; }
};

//装饰镜子的抽象类
class IsMirror : public IsHouse
{
public:
    IsMirror();
    ~IsMirror();
    virtual void function();
}

//装饰镜子的具体的类
class MirrotHouse : public IsMirror
{
private:
    /* data */
public:
    MirrotHouse(/* args */);
    ~MirrotHouse();
    virtual void function() { cout << "this house have a mirror" << endl; }
};

