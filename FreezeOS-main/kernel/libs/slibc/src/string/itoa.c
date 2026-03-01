#include <string.h>

// Integer to string
void itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers for base 10
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;  // Make negetive to positive
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // Append '-' of the number is negetive
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';  // Null-terminate the string

    // Reverse the string
    strrev(str);
}
