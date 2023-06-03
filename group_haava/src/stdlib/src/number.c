#include "system.h"

int isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int atoi(const char *nptr)
{
    int result = 0;
    int sign = 1;
    int index = 0;

    if (nptr[index] == '-') {
        sign = -1;
        index++;
    }

    while (isdigit(nptr[index]))
        result = result * 10 + nptr[index++] - '0';

    return result * sign;
}
