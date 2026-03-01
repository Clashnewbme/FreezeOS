#include <stdint.h>
#include <string.h>

char* strstr(const char* str, const char* substr)
{
    int len = strlen(substr);
    while (*str)
    {
        if (strncmp(str, substr, len) == 0)
        {
            return (char*)str;
        }
        str++;
    }

    return NULL;
}