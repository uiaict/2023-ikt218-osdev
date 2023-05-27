#include "test.h"
#include <stdint.h>




#define VGA_ADDRESS 0xB8000 // The address of the VGA buffer.
#define BUFSIZE 2200        // The buffer size of the VGA buffer.


// This function clears the screen by writing blank spaces to the VGA memory.
void clearScreen()
{
    uint8_t *vga = (uint8_t*) VGA_ADDRESS;
    for (int i = 0; i < BUFSIZE; i++)
    {
        vga[i] = 0;
    }
}
// line len = 20?
void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    int tmp = 0;
    while (*video != 0)
    {
       video = video+ 160;
       tmp = tmp + 160;
    }
    if(tmp>1600){
        clearScreen();
    }
   
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
    
}
