#include "memory.h"

// Simple memset implementation
void *memset(void *dest, int val, unsigned long len)
{
    unsigned char *ptr = dest;
    while (len-- > 0)
        *ptr++ = val;
    return dest;
}
