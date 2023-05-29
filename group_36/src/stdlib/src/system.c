#include "../include/system.h"

#include "../include/system.h"
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

#ifdef __cplusplus
}
#endif