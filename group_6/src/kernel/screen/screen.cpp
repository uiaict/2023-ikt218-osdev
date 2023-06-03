#include "screen.h"

// function to move one line up if the last line is to be written to
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
    // As the memory for screen memory starts at this point we set a pointer here
    char *video = (char*)0xB8000;
    // Making a variable to store the ofset to set the 'cursor' after the first
    int after_grub = 0;

    //Loop to check if there are some data other than ' ' to set the cursor
    for (int i = 0; i < 4000; i+= 2)
    {
        if (video[i] != ' ') {
            after_grub = i;
        } 
    }
    // Take modulus of the number stored in after_grab to find 
    // how many ' ' positions remaining at the last line
    int indent = after_grub%160;
    //Adding a offset in memory to the next line available
    after_grub+= 160 - indent;
    // counter to set which character we are currently on in the string we are passing in
    int counter = 0;

    if (after_grub > 3840) {
        full_screen();
    }
     //Set each character in the sreen and set the color sent in as parameter
    while( string[counter] != 0 )
    { 
       video[after_grub] = string[counter];
       video[after_grub + 1] = colour;  
       counter++;
       after_grub+=2;
    }
}
/*
void clear_screen(int unset_clear){
    char *video = (char)0xB8000;

    for (int i = unset_clear; i < 4000; i+= 2)
    {
        video[i] = ' ';
        video[i+1] = 0x000000;
    }

}
*/


