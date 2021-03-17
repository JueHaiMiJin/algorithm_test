#include <iostream>
#include <cstdio>
#include <cstdarg>

using namespace std;

int add(int num, ...)
{
    va_list valist;
    int sum = 0;
    int i = 0;

    va_start(valist, num);

    for(i = 0; i < num; i++)
    {
        sum += va_arg(valist, int);
    }

    va_end(valist);
    return sum;
}

float add(char* format, ...)
{
    va_list ap;
    int d;
    double f;
    float sum = 0;
    va_start(ap, format);
    while (*format)
    {
        if('%' == *format )
        {
            switch (*(++format))
            {
            case 'f':
                f = va_arg(ap, double);
                sum += f;
                break;
            case 'd':
                d = va_arg(ap, int);
                sum += d;
                break;
            default:
                break;
            }
        }
        ++format;
    }
    va_end(ap);
    return sum;
}

int main(int argc, char** argv)
{
    int a = 5;
    int b = 6;
    int sum = add(2, a, b);
    std::cout << "sum " << sum << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    int s = 5;
    float f = 6.1;
    float newsum = add("%d, %f", s, f);
    std::cout << "newsum " << newsum << std::endl;

    return 0;
}