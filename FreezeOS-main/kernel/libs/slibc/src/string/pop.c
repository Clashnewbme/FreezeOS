#include <stddef.h>
#include <string.h>

// Remove the last caharcter of a string
void pop(char* str)
{
    size_t len = strlen(str);

    if (len > 0)
    {
        str[len - 1] = '\0';  // Remove the last character
    }
}