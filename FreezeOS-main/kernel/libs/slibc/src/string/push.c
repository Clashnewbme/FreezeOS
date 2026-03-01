#include <stddef.h>
#include <string.h>

// Push a new character at the end of the string
void push(char* str, char c)
{
    size_t len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}