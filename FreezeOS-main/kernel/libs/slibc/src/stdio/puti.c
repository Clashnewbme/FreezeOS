#include <stdio.h>
#include <string.h>

// Example implementation of print_int assuming screen output functions exist
void puti(int n)
{
    // Create a empty array with length equal to the counts of the number to
    // hold the returen string
    char str[count_digits(n)];
    itoa(n, str, 10);

    // Assuming you have a function to print strings to the screen
    puts(str);  // Replace with your screen output function
}