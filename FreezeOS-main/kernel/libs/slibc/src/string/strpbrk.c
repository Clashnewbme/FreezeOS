#include <stddef.h>

char* strpbrk(const char* str, const char* accept)
{
    const char* s;
    const char* a;

    for (s = str; *s; ++s)
    {
        for (a = accept; *a; ++a)
        {
            if (*s == *a)
            {
                return (char*)s;
            }
        }
    }

    return NULL;
}