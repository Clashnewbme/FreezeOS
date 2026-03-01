#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Function to extract a substring
char* substr(const char* src, int start, int length)
{
    int src_len = strlen(src);
    // Validate the input
    if (src == NULL || start < 0 || length < 0 || start >= src_len)
    {
        return NULL;
    }

    // Adjust the length if its goes beyond the src string
    if (start + length > src_len)
    {
        length = src_len - start;
    }

    // Allocase memory for the substring
    char* result = (char*)malloc(length + 1);

    // Copy the substring
    strncpy(result, src, length);
    result[length] = '\0';  // Null-terminate the string

    return result;
}