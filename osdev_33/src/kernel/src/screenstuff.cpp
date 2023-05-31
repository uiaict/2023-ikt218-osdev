#include "screenstuff.h"

void clear_screen()
{
    volatile char *video = (volatile char*)0xB8000;

    for(int i = 0; i < 80 * 25; i++) {
        *video++ = ' '; // character
        *video++ = 0; // attribute-byte
    }
}

// Define write_string function
void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB84AA;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}