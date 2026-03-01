#include <stddef.h>

size_t strspn(const char* str, const char* accept)
{
    const char* s;
    const char* a;
    size_t count = 0;

    for (s = str; *s; ++s)
    {
        for (a = accept; *a; ++a)
        {
            if (*s == *a)
            {
                break;
            }
        }

        if (*a == '\0')
        {
            return count;
        }

        ++count;
    }

    return count;
}
