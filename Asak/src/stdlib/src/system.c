#include "system.h"

size_t strlen(const char *s)
{
    int length = 0;
    while (s[length])
    {
        length++;
    }
    return length;
}