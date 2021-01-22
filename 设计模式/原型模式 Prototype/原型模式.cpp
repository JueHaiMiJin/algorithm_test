// 用原型实例制定创建对象的种类，并且通过拷贝这些原型创建新的对象
// 从一个对象再创建另外一个可定制的对象，而且不需要知道任何创建的细节。 c++ 本身是有拷贝构造的，那么原型模式有什么好处呢？
// 我自己感觉，和拷贝构造相比，隐藏了拷贝的细节，把拷贝构造进行了封装
// 下面这个例子，我用了继承和多态，再加上智能指针，用起来给我自己对大的感受就是不用动脑子，我都不需要知道这具体是哪一个子类

#include <iostream>

using namespace std;

class Person
{
private:
    string name;
    int age;
public:
    Person(string in_name, int in_age) : name(in_name),age(in_age){};
    ~Person();
    virtual void show() {cout << "I am " << name << " i am " << age << " years old" << endl; }
    virtual Person* clone() { return new Person(*this); }
};

class Boy:public Person
{
public:
    Boy(string b_name, int b_age): Person(b_name, b_age) {};
    ~Boy();
    virtual void show() { cout << "I am boy" << endl; }
    virtual Person *clone() { return new Boy(*this); }
};

class Girl : public Person
{
public:
    Girl(string b_name, int b_age) : Person(b_name, b_age){};
    ~Girl();
    virtual void show() { cout << "I am girl" << endl; }
    virtual Person *clone() { return new Girl(*this); }
};

int main(int argc, char const *argv[])
{
    Person* a_boy = new Boy("ceshi", 10);
    Person *a_girl = new Girl("ceshi2", 19);

    //直接拷贝不适用原形模式
    Person* clone1(new Boy(*dynamic_cast<Person *>(a_boy)));
    clone1->show();

    //使用原形模式
    Person *clone2(a_girl->clone());
    clone2->show();
    return 0;
}

