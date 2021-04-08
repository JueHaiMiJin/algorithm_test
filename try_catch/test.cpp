#include <iostream>
#include <string>
using namespace std;
int CountTax(int salary)
{
    try
    {
        if (salary < 0)
            throw string("zero salary");
        cout << "counting tax" << endl;
    }
    catch (string s)
    {
        cout << "CountTax error : " << s << endl;
        throw; //继续抛出捕获的异常
    }
    cout << "tax counted" << endl;
    return salary * 0.15;
}
int main()
{
    double f = 1.2;
    try
    {
        CountTax(-1);
        cout << "end of try block" << endl;
    }
    catch (string s)
    {
        cout << s << endl;
    }
    cout << "finished" << endl;
    return 0;
}