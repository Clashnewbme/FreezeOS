#include <stddef.h>
#include <stdio.h>
#include <string.h>

char* strtok(char* str, const char* delim)
{
    static char* last;
    if (str == NULL)
    {
        str = last;
    }

    if (str == NULL)
    {
        return NULL;
    }

    // Skip leading delimiters
    // str += strspn(str, delim);
    // if (*str == '\0')
    // {
    //     last = NULL;
    //     return NULL;
    // }

    char* token = str;
    str = strpbrk(str, delim);

    if (str)
    {
        *str = '\0';
        last = str + 1;
    }
    else
    {
        last = NULL;
    }

    return token;
}