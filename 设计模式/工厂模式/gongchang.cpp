#include <iostream>
using namespace std;

//简单工程模式
class fruit
{
private:
    /* data */
public:
    fruit(/* args */);
    ~fruit();
};


class apple : public fruit
{
private:
    /* data */
public:
    apple(/* args */);
    ~apple();
};

class origen : public fruit
{
private:
    /* data */
public:
    origen(/* args */);
    ~origen();
};

class fruitfactory
{
private:
    /* data */
public:
    fruitfactory(/* args */);
    fruit *CreateFruit(string type);
    ~fruitfactory();
};
fruit* fruitfactory::CreateFruit(string type)
{

    if(type.compare("apple"))
        return new apple();
    else if(type.compare("orieng"))
        return new origen();
    else
        return NULL;
}

//简单工厂模式因为可以创建多个不同的类所以不符合：单一职责原则；当工厂需要添加新的水果时需要修改既有的类，违反开闭原则（修改时只要添加新的类而不是修改既有的类）


//工厂模式
class apple
{
private:
    /* data */
public:
    apple(/* args */);
    ~apple();
};

class appleFactory
{
private:
    /* data */
public:
    appleFactory(/* args */);
    apple *Create();
    ~appleFactory();
};
apple* appleFactory::Create()
{
    return new apple();
}
.
.
.

//每个工厂生产一种水果，修改时也符合专一原则，开闭原则也符合
