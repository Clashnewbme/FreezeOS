#include <stddef.h>
#include <string.h>

void strsplit(char* str, char** pointers, char* delim)
{
    char* token = strtok(str, delim);
    int count = 0;

    while (token != NULL)
    {
        pointers[count] = token;
        count++;
        token = strtok(NULL, delim);
    }
}