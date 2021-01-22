#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


bool IsStrValid(char* str)
{
    if(strlen(str)%2)
        return false;
    
    
}

int main(int argc, char const *argv[])
{
    char* str = "({[]})";
    bool ret = IsStrValid(str);
    printf("ret: %d \n", ret);
    return 0;
}
