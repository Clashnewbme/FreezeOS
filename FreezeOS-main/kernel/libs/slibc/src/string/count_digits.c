int count_digits(int n)
{
    int count = 0;

    // Handle the special case of 0
    if (n == 0)
    {
        return 1;
    }

    // Handle negative ns
    if (n < 0)
    {
        n = -n;
    }

    // Count the n of digits
    while (n != 0)
    {
        n /= 10;
        count++;
    }

    return count;
}