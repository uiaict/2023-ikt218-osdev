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
void write_string( int line, int column, int colour, const char *string )
{
    volatile char *video = (volatile char*)(0xB8000 + line * 160 + column * 2);
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}



void print_pattern(const char* pattern[], int num_lines, int start_pos) {
    for (int i = 0; i < num_lines; i++) {
        const char* line = pattern[i];
        volatile char *video = (volatile char*)(0xB8000 + (start_pos + i) * 160);
        while (*line != 0) {
            *video++ = *line++;
            *video++ = 10; 
        }
    }
}