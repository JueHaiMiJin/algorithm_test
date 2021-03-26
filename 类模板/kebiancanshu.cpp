#include <iostream>
using namespace std;

#if 0
template <typename... a>
class Car
{
};
template <typename... A>
class BMW : public Car<A...>
{
};
BMW<int, char> car;
// A...称之为包扩展(pack extension)，包扩展是可以传递的。

template <class... T>
void f(T... args)
{
    cout << sizeof...(args) << endl; //打印变参的个数
}
#endif

#if 0
//递归终止函数   特化的模板函数
void print()
{
    cout << "empty" << endl;
}
//展开函数
template <class T, class... Args>
void print(T head, Args... rest)
{
    cout << "parameter " << head << endl;
    print(rest...);
}

//sum例子
template <typename T>
T sum(T t)
{
    return t;
}
template <typename T, typename... Types>
T sum(T first, Types... rest)
{
    return first + sum<T>(rest...);
}
#endif

template <class T>
void print(T t)
{
    cout << t << endl;
}

template <class... Args>
void expand(Args... args)
{
    int arr[] = {(print(args), 0)...};
}

expand(1, 2, 3, 4);
//用到数组的初始化列表，这个数组的目的纯粹是为了在数组构造的过程展开参数包。
//{(printarg(args), 0)...}将会展开成((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0),  etc... )，
//最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]。printarg便会处理参数包中每一个参数。

//支持lambda表达式 
template <class F, class... Args>
void expand(const F &f, Args &&...args)
{ 
    //这里用到了完美转发
    initializer_list<int>{(f(std::forward<Args>(args)), 0)...};
}

expand([](int i) { cout << i << endl; }, 1, 2, 3);

int main()
{
    f();           //0
    f(1, 2);       //2
    f(1, 2.5, ""); //3
    return 0;
}

