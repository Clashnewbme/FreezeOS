#include <stddef.h>

// Compare string for maximum n times
int strncmp(const char* a, const char* b, size_t n)
{
    while (n && *a && (*a == *b))
    {
        a++;
        b++;
        n--;
    }

    if (n == 0)
    {
        return 0;
    }

    return *(unsigned char*)a - *(unsigned char*)b;
}