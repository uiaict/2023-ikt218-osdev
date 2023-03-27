#include "system.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_SIZE 4    

#define NEWLINE '\n'
#define TAB '\t'
volatile char *video = (volatile char*)0xB8000; // Memory address of beginning of text mode with color
int x = 0;                                      // Current screen column 
int y = 0;                                      // Current screen row


int printf(const char *format, ...)
{
    /*
    * Function for printing to terminal in VGA text mode.
    * Supports newline and tabular characters.
    * 
    * Scrolling in text mode is not implemented yet.
    * 
    * Implementation based of examples given at 
    * https://wiki.osdev.org/Printing_To_Screen
    * */

    //volatile char *video = (volatile char*)0xB8000; // Memory address of beginning of text mode with color
    //int x = 0;                                      // Current screen column 
    //int y = 0;                                      // Current screen row
    int length = 0;                                 // Amount of characters printed

    while( *format != 0 )
    {
        if (*format == NEWLINE)
        {
            // Increment by multiple of 2 since text mode assigns two bytes to each character (ASCII code and color attribute)
            video += 2*(VGA_WIDTH - x);
            format++;                               // Move to next input character
        
            x = 0;
            y++;
        }
        else if (*format == TAB)
        {
            if ( x + TAB_SIZE > VGA_WIDTH)
            {
                // Stop tabular from overflowing to next line
                video += 2*(VGA_WIDTH - x);
            }
            else
            {
                video += 2*(TAB_SIZE);
            }
            
            format++;
            x += TAB_SIZE;
        }
        else
        {
            *video++ = *format++;                   // Output current character to screen and increment pointers by 1 byte
            *video++ = 0xD0;                        // Set color attribute and increment pointer
            x++;
            length++;
        }

        if (x >= VGA_WIDTH)
        {
            // Update column and row pointers when 'overflowing' to next line
            x = 0;
            y++;
        }

        if (y > VGA_HEIGHT)
        {
            // Scrolling functionality

            //video = (volatile char*)0xB8000;
            //y=0;
        }
    }

    return length;
}
