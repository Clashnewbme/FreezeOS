// Counts the number of character in the string.
int strlen(const char* s)
{
    int len = 0;
    // Process four characters at a time if possible
    for (; *s && *(s + 1) && *(s + 2) && *(s + 3); s += 4)
    {
        len += 4;
    }

    // Handle the remaining characters
    while (*s)
    {
        len++;
        s++;
    }
    return len;
}