// 组合模式

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Componet
{
protected:
    string m_str;

public:
    Componet(string str)
    {
        m_str = str;
    }
    ~Componet();

    virtual void Add(Componet *p) = 0;
    virtual void Remove(Componet *p) = 0;
    virtual void diaplay() = 0;
    virtual string get() { return m_str; }
};

class Leaf : public Componet
{
private:
    /* data */
public:
    Leaf(string str) : Componet(str) {}
    ~Leaf();
    virtual void Add(Componet *p) { cout << "Add Leaf" << endl; }
    virtual void Remove(Componet *p) { cout << "Remove Leaf" << endl; }
    virtual void diaplay() { cout << "Name " << m_str << endl; }
};

class Node : public Componet
{
private:
    vector<Componet *> m_vect;

public:
    Node(string str) : Componet(str) {}
    ~Node()
    {
        if (!m_vect.empty())
            m_vect.clear();
    }
    virtual void Add(Componet *p) { m_vect.push_back(p); }

    virtual void Remove(Componet *p)
    {
        vector<Componet *>::iterator it = m_vect.begin();
        for (; it != m_vect.end(); it++)
        {
            if (p->get() == (*it)->get())
                m_vect.erase(it);
        }
    }

    virtual void diaplay()
    {
        vector<Componet *>::iterator it = m_vect.begin();
        for (; it != m_vect.end(); it++)
        {
            (*it)->diaplay();
        }
    }
};

int main(int argc, char const *argv[])
{
    Node *p = new Node("总部");
    p->Add(new Leaf("总部财务部门"));
    p->Add(new Leaf("总部人力资源部门"));
    p->diaplay();
    cout << "***************************** \n";
    Node *p1 = new Node("上海分部");
    p1->Add(new Leaf("上海分部财务部门"));
    p1->Add(new Leaf("上海分部人力资源部门"));
    p1->diaplay();
    cout << "***************************** \n";
    p->Add(p1);
    p->diaplay();
    return 0;
}
