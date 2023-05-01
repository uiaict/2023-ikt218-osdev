#include "screen.h"
#include <stdint.h>




#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200



// This function clears the screen by writing blank spaces to the VGA memory.
void clearScreen()
{
    uint8_t *vga = (uint8_t*) VGA_ADDRESS;
    for (int i = 0; i < BUFSIZE; i++)
    {
        vga[i] = 0;
    }
}

// This function writes a string to the VGA memory, so that it is displayed on the screen.
void printString(char * string)
{
    char * vgaBuffer = (char*)VGA_ADDRESS;
    while(*string != 0)
    {
        *vgaBuffer++ = *string++;
        *vgaBuffer++ = 15;
    }
}