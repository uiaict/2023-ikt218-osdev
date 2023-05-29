#include "screen.h"

void full_screen() {
    char *video = (char*)0xB8000;

    for (int i = 0; i < 4000; i+=2)
    {
        video[i] = video[i + 160];
        video[i + 1] = video[i + 161];
    }
}


void write_string( int colour, const char *string)
{
    char *video = (char*)0xB8000;
    int after_grub = 0;

    for (int i = 0; i < 4000; i+= 2)
    {
        if (video[i] != ' ') {
            after_grub = i;
        } 
    }
    int indent = after_grub%160;
    after_grub+= 160 - indent;
    int counter = 0;

    if (after_grub > 3840) {
        full_screen();
    }
    while( string[counter] != 0 )
    { 
       video[after_grub] = string[counter];
       video[after_grub + 1] = colour;  
       counter++;
       after_grub+=2;
    }
}


