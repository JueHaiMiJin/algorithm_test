#include <iostream>

using namespace std;

class Mode{
    public:
        Mode() {};
        ~Mode() {}

        void print()
        {
            cout << "name " << name()
            << " birthday " << birthday() << endl;
        }
    virtual string name() = 0;
    virtual string birthday() = 0;
};

class test : public Mode
{
private:
    string m_name;
    string m_birthday;
public:
    test(string name, string birthday):m_name(name), m_birthday(birthday) {}
    ~test() {}
    string name() { return m_name; }
    string birthday() { return m_birthday; }
};


int main(int argc, char const *argv[])
{
    test* me = new test("Magic Yang", "2000-01-10");
    me->print();
    return 0;
}


