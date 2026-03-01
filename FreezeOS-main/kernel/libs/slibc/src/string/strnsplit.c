#include <stddef.h>
#include <stdio.h>
#include <string.h>

void strnsplit(char* str, char** pointers, char* delim, int max)
{
    char* token = strtok(str, delim);
    int count = 0;

    while (token != NULL && count <= max)
    {
        pointers[count] = token;
        count++;
        token = strtok(NULL, delim);
    }
}