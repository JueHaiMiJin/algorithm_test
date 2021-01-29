#include <iostream>
#include <sstream>

using namespace std;

#define M_HEX_0(n) ((((n) >> 4 & 0xF) > 9) ? (((n) >> 4 & 0xF) - 10 + 'A') : (((n) >> 4 & 0xF) + '0'))

int main()
{
    string str;
    str += M_HEX_0(240);
    cout << "str " << str << endl;
    return 0;
}