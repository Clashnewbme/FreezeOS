#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "format_string.h"

// Formate a string and print into the console
void printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char* str = format_string(format, args);
    if (str != NULL)
    {
        puts(str);
        free(str);
    }
    va_end(args);
}