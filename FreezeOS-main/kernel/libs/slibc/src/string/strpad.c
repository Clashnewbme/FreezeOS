#include <stdio.h>
#include <string.h>

void strpad(char* str, int max, char c)
{
    int len = strlen(str);
    if (len < max)
    {
        memset(str + len, c, max - len);
        str[max] = '\0';
    }
}