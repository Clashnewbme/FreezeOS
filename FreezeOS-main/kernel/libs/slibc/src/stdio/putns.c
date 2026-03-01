#include <console.h>
#include <stddef.h>

// Print characters n number of times
void putns(const char* str, size_t n)
{
    while (n--)
    {
        putchar(*str++);
    }
}