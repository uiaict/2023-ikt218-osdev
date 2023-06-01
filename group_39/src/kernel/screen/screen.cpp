#include "screen.h"
#include <stdint.h>


#define VGA_ADDRESS 0xB8000 // The address of the VGA buffer.
#define BUFSIZE 4000       // The buffer size of the VGA buffer (80x25 characters, 2 bytes per character)

uint64_t cursor_position = 0;

// This function clears the screen by writing blank spaces to the VGA memory.
void clearScreen()
{
    // This defines a blank, black character to fill the screen with
    uint16_t blankCharacter = 0x20; // Space
    uint16_t blankColour = 0x0F ; // Black with white text
    uint8_t *vga = (uint8_t*) VGA_ADDRESS;
    for (int i = 0; i < BUFSIZE; i++)
    {
        *vga++ = blankCharacter;
        *vga++ = blankColour;
    }
}

// This function writes a string to the VGA memory, so that it is displayed on the screen.
void printString(char * string)
{
    char * vgaBuffer = (char*)VGA_ADDRESS;
    vgaBuffer += cursor_position*2;
    while(*string != 0)
    {
        *vgaBuffer++ = *string++; // Print a single character to the screen.
        *vgaBuffer++ = 15; // Print text in colour 'WHITE'.
        cursor_position++;
    }
}



// This function writes a char to the VGA memory, so that it is displayed on the screen.
void printChar(char ch)
{
    char * vgaBuffer = (char*)VGA_ADDRESS;
    vgaBuffer += cursor_position*2;
    *vgaBuffer++ = ch; // Print a single character to the screen.
    *vgaBuffer++ = 15; // Print text in colour 'WHITE'. 
    cursor_position++;
}