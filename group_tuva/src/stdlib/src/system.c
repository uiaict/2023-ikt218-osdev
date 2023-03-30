#include "system.h"
#include "stdbool.h"

int printf(const char *string, ...)
    {
        volatile char *video = (volatile char*)0xB8000;
        while( *string != 0 )
        {
            *video++ = *string++;
            *video++ = 0x0F;
        }
    }



