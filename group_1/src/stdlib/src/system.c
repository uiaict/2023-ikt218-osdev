#include "system.h"
#define VIDEO_MEMORY_ADDRESS 0xB8000
#define VIDEO_MEMORY_SIZE 80*25*2 //80 columns x 25 rows x 2 bytes per character

void clear_screen()
{
    volatile char *video = (volatile char*)VIDEO_MEMORY_ADDRESS;
    for (int i = 0; i < VIDEO_MEMORY_SIZE; i += 2)
    {
        // Set the character to space (0x20) and attribute to black on black (0x00)
        *video++ = 0x20;
        *video++ = 0x00;
    }
}
void write_string(unsigned char colour, const char *string) 
{ 
    if (string == NULL) {
        return;
    }
    volatile char *video = (volatile char*)VIDEO_MEMORY_ADDRESS; 
    while (*string != '\0') 
    { 
        *video++ = *string++; 
        *video++ = (char)colour; 
    } 
}