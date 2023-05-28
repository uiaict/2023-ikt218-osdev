#include "../include/system.h"

#include <stdint.h>
#include <time.h>
#include <stdio.h>

void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}