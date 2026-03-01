// Set memory spaces to c
void memset(char* ptr, char c, int count)
{
    while (count--)
    {
        *ptr++ = c;
    }
}