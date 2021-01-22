#include <iostream>

using namespace std;


class Iuser{
public:
    Iuser() {}
    ~Iuser() {}
    virtual void interview() = 0;
};

class SwitchState{
public:
    SwitchState() {}
    ~SwitchState() {}
    virtual void update() = 0;
    virtual void expire() = 0;
};

class NormalUser : public Iuser
{
public:
    NormalUser() {}
    ~NormalUser() {}
    void interview() { cout << "please upfate to plus " << endl; }
};

class PlusUser : public Iuser
{
public:
    PlusUser() {}
    ~PlusUser() {}
    void interview() { cout << "The interview is starting... " << endl; }
};

class User : public Iuser, public SwitchState
{
private:
    Iuser *m_user = new NormalUser();
public:
    User() {}
    ~User() {}

    void interview() { m_user->interview(); }
    void update() { m_user = new PlusUser(); }
    void expire() { m_user = new NormalUser(); }
};


int main(int argc, char const *argv[])
{
    User me;
    me.interview();
    me.update();
    me.interview();
    me.expire();
    me.interview();
    return 0;
}


