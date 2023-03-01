#include "print.h"
#include <stdarg.h>
#include <stdio.h>

//Defines the function terminal_putchar, that prints a single character to the terminal.
void terminal_putchar(char c)
{
    //pointer to memory location
    //GPU will auto display characters stored at 0xb8000
    uint16_t* VideoMemory = (uint16_t*)0xb8000;

    //Declares cursor variables
    static uint8_t x=0, y=0;

    //Switch statement that takes in the entered character.
    switch(c)
    {
        //If the entered character is a newline the y/vertical cursor is incremented by 1, and the x/horizontal cursor is set to 0
        case '\n':
            y++;
            x = 0;
            break;
        //If the character is any other character it gets placed at the current position of the cursors, then the x/horizontal cursor gets incremented.
        default:
            VideoMemory[VGA_WIDTH*y+x] = (VideoMemory[VGA_WIDTH*y+x] & 0xFF00) | c;
            x++;
            break;
        }

    //If the horizontal cursor reaches the edge of the screen the y/vertical cursor is incremented and the x/horizontal cursor gets set to 0.
    if(x >= VGA_WIDTH)
    {
        y++;
        x = 0;
    }

    //If the cursor reaches the bottom of the screen the whole screen gets reset.
    if(y >= VGA_HEIGHT){
         //set whole screen to space character
        for(y = 0; y < VGA_HEIGHT; y++)
        {
            for(x = 0; x < VGA_WIDTH; x++)
            {
                VideoMemory[VGA_WIDTH*y+x] = (VideoMemory[VGA_WIDTH*y+x] & 0xFF00) | ' ';
            }
        }
        //Sets the y/vertical cursor, and the x/horizontal cursor to 0.
        x=0;
        y=0;
    }
}

//Function that works like printf.
void print(char* str, ...)
{
    //Sets up an argument list args that takes in a variable number of additional arguments, that can be accessed by a va_list named args.
    va_list args;
    //Initializes the start of the args list with the str argument.
    va_start(args, str);

    //While loop that loops through every char in the string str until it reaches the null character.
    while(*str != '\0'){

        //If statement checks if the current character is a '%'
        if ( *str != '%')
        {
            //If the current character is not a '%' it prints the character to the terminal, increments the str, and starts the while loop again from the top.
            terminal_putchar(*str);
            str++;
            continue;
        }

        //If we have found a '%' we want the character after so we increment the str.
        str++;
        
        //Switch statement based on the current character.
        switch (*str)
        {
            //If the current character is a 'c' the next argument in the va_arg list is a character
            case 'c':
            {
                //Print the character to the terminal and increment the str.
                terminal_putchar(va_arg(args, const char*));
                str++;
                break;
            }
        
            //If the current character is a 's' the next argument in the va_arg list is a string
            case 's':
            {
                //Loop through the string and print every character to the terminal, then increment the str.
                const char* s = va_arg(args, const char*);
                while(*s != '\0')
                {
                    terminal_putchar(*s);
                    *s++;
                }
                str++;
                break;
            }

            //If the current character is a 'd' the next argument in the va_arg list is an integer.
            case 'd':
            {
                //Set up a variable num equal to the integer in the va_arg list, and a variable nstr.
                int num = va_arg(args, int);
                char nstr[50];
                //Turn the int num into a string and store it in the variable nstr.
                int_to_string(nstr, num);
                //Set up a character ptr that is equal to the nstr string.
                char* ptr = nstr;

                //Loop through every character in the ptr and print it to the terminal. And finally increment the str.
                while(*ptr != '\0')
                {
                    terminal_putchar(*ptr);
                    *ptr++;
                }
                str++;
                break;
            }

            //If the current character is a 'f' the next argument in the va_arg list is a float.
            case 'f':
            {
                //Set up a variable f equal to the float in the va_arg list, and a variable nstr.
                float f = va_arg(args, double);
                char nstr[50];
                //Turn the float f into a string and store it in the variable nstr with a precission of 4.
                float_to_string(nstr, f, 2);
                //Set up a character ptr that is equal to the nstr string.
                char* ptr = nstr;

                //Loop through every character in the ptr and print it to the terminal. And finally increment the str.
                while(*ptr != '\0')
                {
                    terminal_putchar(*ptr);
                    *ptr++;
                }
                str++;
                break;
            }
        }
    }
    //Calls the va_end function that frees any resources associated with the list.
    va_end(args);
}