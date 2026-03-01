#include <string.h>

char* strcat(char* dest, const char* src)
{
    char* ptr = dest + strlen(dest);
    while (*src)
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}