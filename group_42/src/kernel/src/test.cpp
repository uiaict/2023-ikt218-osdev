#include "test.h"
#include <stdint.h>






// Deprecated version of the implementation in the IJI_OS class, but it is still called in one location
void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    int tmp = 0;
    while (*video != 0)
    {
       video = video+ 160;
       tmp = tmp + 160;
    }
 
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
    
}
