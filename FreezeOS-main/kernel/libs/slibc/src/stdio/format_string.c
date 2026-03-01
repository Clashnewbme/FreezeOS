#include <stddef.h>
#include <stdio.h>
#include <string.h>

char* format_string(const char* format, va_list args)
{
    // Allocate memory space for the formated string
    char* str = malloc(MAX_BUFFER_SIZE);
    if (str == NULL)
    {
        return NULL;
    }

    // Clear old data in memory
    memset(str, 0, MAX_BUFFER_SIZE);
    for (const char* p = format; *p != '\0'; p++)
    {
        if (*p == '%' && *(p + 1) != '\0')
        {
            p++;  // Move to the format specifier
            switch (*p)
            {
                int i;
                char buffer[20];

                case 'd':
                    i = va_args(args, int);
                    itoa(i, buffer, 10);  // Convert integer into string
                    strcat(str, buffer);
                    break;
                case 'n':
                    i = va_args(args, int);
                    itoa(i, buffer, 10);  // Convert integer into string
                    strcat(str, buffer);
                    break;
                case 's':
                    char* s = va_args(args, char*);
                    strcat(str, s);
                    break;
                case 'c':
                    int c = va_args(args, int);  // I don't know more about it
                    push(str, c);
                    break;
                default:
                    push(str, '%');
                    push(str, *p);
                    break;
            }
        }
        else
        {
            push(str, *p);  // Print the character
        }
    }

    return str;
}