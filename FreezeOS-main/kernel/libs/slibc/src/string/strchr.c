#include <stddef.h>
#include <string.h>

// find the first occurance of the c and return the index
char* strchr(const char* str, int c)
{
    while (*str)  // Loop untill we reach the end of the string
    {
        if (*str == (char)c)
        {
            return (char*)str;
        }
        str++;
    }

    if (*str == (char)c)  // Check if the character is at the end of the string
    {
        return (char*)str;
    }

    return NULL;  // If not match return NULL
}