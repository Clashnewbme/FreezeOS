#include <console.h>
#include <stdint.h>

// Print a string into console
void puts(const char* s)
{
    while (*s)
    {
        putchar(*s++);
    }
}

void d(char* title, char* data)
{
    puts(title);
    puts(" : ");
    puts(data);
    hr();
}