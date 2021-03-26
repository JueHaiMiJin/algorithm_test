#include <iostream>
using namespace std;

int main()
{
    template <class... T>
    void f(T... args)
    {
        cout << sizeof...(args) << endl; //打印变参的个数
    }

    f();           //0
    f(1, 2);       //2
    f(1, 2.5, ""); //3
    return 0;
}

