//回文检测
#include <iostream>
#include <string>


using namespace std;

auto main(int argc, char* argv[])->int
{
    string s = "abbasy";
    int top = 0;
    for(auto ch:s)
    {
        if(top == 0 || s[top -1] != ch)
            s[top++] = ch;
        else
            --top;
    }
    s.resize(top);
    cout << "s: " << s << endl;
    return 0;
}