#include <iostream>

using namespace std;

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

class factory
{
    factory(){};
    ~factory(){};
    virtual fruit* Create()
    {
        return new fruit();
    }
};

class applefactory : public factory
{
    applefactory();
    ~applefactory();
    virtual fruit *Create()
    {
        return new apple();
    }
};

class origenfactory : public factory
{
    origenfactory();
    ~origenfactory();
    virtual fruit *Create()
    {
        return new origen();
    }
};
