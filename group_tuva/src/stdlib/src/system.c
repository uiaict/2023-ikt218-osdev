#include "system.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "time.h"

void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}
int printf(const char *string, ...)
    {
        volatile char *video = (volatile char*)0xB8000;
        while( *string != 0 )
        {
            *video++ = *string++;
            *video++ = 0x0F;
        }
    }

int print_new_line(){
    
}



