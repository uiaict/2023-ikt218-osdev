#include "screen.h"
#include <stdarg.h>
#include "ports.h"
#include "strings.h"


//Setting up the width and height of the vga.
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

//Sets up the VGA video mode buffer.
uint16_t *terminal_buffer = (uint16_t *)0xB8000;

//Setting up the cursor variables.
static int terminal_column = 0;
static int terminal_row = 0;

//Holds the terminal color.
static uint8_t terminal_color;

//The function takes the foreground and background colors for a VGA text mode character and returns an 8-bit value representing the combined color.
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
//The function combines the character and color information into a single 16-bit value representing a VGA-compatible text mode character.
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
//Sets the terminal_color variable.
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

static void move_cursor()
{
    uint16_t cursor_location = terminal_row * 80 + terminal_column;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursor_location >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursor_location);      // Send the low cursor byte.

    // Turn on the cursor by setting the cursor start and end registers.
    outb(0x3D4, 0x0A); // cursor start register
    outb(0x3D5, 0x00); // set the cursor start to 0
    outb(0x3D4, 0x0B); // cursor end register
    outb(0x3D5, 0x0F); // set the cursor end to 15 (turn on the cursor)
}

//Function that scrolls the terminal up by one line.
void scroll_up()
{
    //Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    //Row 0 is the top, this means we need to scroll up
    if (terminal_row <= 0)
    {
        // Move the current text chunk that makes up the screen
        // forward in the buffer by a line
        int i;
        for (i = 1*80; i <= 25*80; i++)
        {
            terminal_buffer[i - 80] = terminal_buffer[i];
        }

        // The first line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            terminal_buffer[i] = blank;
        }
        // The cursor should now be on the first line.
        terminal_row = 0;
    }
}

//Function that scrolls the terminal up by one line.
void scroll_down()
{
    //Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    //Row 25 is the end, this means we need to scroll up
    if(terminal_row >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            terminal_buffer[i] = terminal_buffer[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            terminal_buffer[i] = blank;
        }
        // The cursor should now be on the last line.
        terminal_row = 24;
    }
}

//Function that fills the terminal with spaces.
void terminal_clear(void) 
{
    // Make an attribute byte for the default colours
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    //For loop that fills the terminal with blank characters.
    for (int i = 0; i < 80*25; i++)
    {
        terminal_buffer[i] = blank;
    }

    //Move the hardware cursor back to the start.
    terminal_column = 0;
    terminal_row = 0;
    move_cursor();
}

//Function that works like a backspace button.
void backspace()
{   
    //If the terminal_column and terminal_row are both 0, there is nothing to remove, so we just return.
    if(terminal_column == 0 && terminal_row == 0)
    {
        return;
    }
    //If the terminal_column / x coordinate is 0
    else if(terminal_column == 0)
    {
        //Decrement the terminal_row/y coordinate.
        terminal_row--;

        //Find the last non-blank character in the previous line, ignoring newline characters
        int last_non_blank = VGA_WIDTH - 1;
        while (last_non_blank >= 0 && (terminal_buffer[VGA_WIDTH * terminal_row + last_non_blank] & 0xFF) == ' ')
        {
            last_non_blank--;
        }

        // If the last non-blank character is a newline character, place the cursor at the beginning of the line
        if (last_non_blank == -1 || (terminal_buffer[VGA_WIDTH * terminal_row + last_non_blank] & 0xFF) == '\n') 
        {
            terminal_column = 0;
        }
        // Otherwise, set the terminal_column/x coordinate to the last non-blank character in the previous line
        else 
        {
            terminal_column = last_non_blank + 1;
        }
    }
    //Else we are somewhere in a line that's not the start.
    else
    {   
        //Decrement the terminal_column/x coordinate.
        terminal_column--;
    }
    //Fill the current cursor position with a blank character.
    terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] = (terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] & 0xFF00) | ' ';
    //Move the cursor.
    move_cursor();
}

//Defines the function terminal_putchar, that prints a single character to the terminal.
void terminal_putchar(char c)
{
    //Switch statement that takes in the entered character.
    switch(c)
    {
        //If the entered character is a newline the y/vertical cursor is incremented by 1, and the x/horizontal cursor is set to 0
        case '\n':
            terminal_row++;
            terminal_column = 0;
            break;
        //If the character is any other character it gets placed at the current position of the cursors, then the x/horizontal cursor gets incremented.
        default:
            terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] = (terminal_buffer[VGA_WIDTH*terminal_row+terminal_column] & 0xFF00) | c;
            terminal_column++;
            break;
        }

    //If the horizontal cursor reaches the edge of the screen the y/vertical cursor is incremented and the x/horizontal cursor gets set to 0.
    if(terminal_column >= VGA_WIDTH)
    {
        terminal_row++;
        terminal_column = 0;
    }

    //If the cursor reaches the bottom of the screen scroll down.
    if(terminal_row >= VGA_HEIGHT)
    {
        scroll_down();
    }
    //Move the cursor
    move_cursor();
}

//Function that works like printf.
void printf(char* str, ...)
{
    //Sets up an argument list args that takes in a variable number of additional arguments, that can be accessed by a va_list named args.
    va_list args;
    //Initializes the start of the args list with the str argument.
    va_start(args, str);

    //While loop that loops through every char in the string str until it reaches the null character.
    while(*str != '\0')
    {

        //If statement checks if the current character is a '%'
        if (*str != '%')
        {
            //If the current character is not a '%' it prints the character to the terminal, and increments the str.
            terminal_putchar(*str);
            str++;
            
            //Starts the while loop again from the top.
            continue;
        }

        //If we have found a '%' we want the character after so we increment the str.
        str++;
        
        //Switch statement based on the current character.
        switch (*str)
        {
            //If there are two %% characters after eachother print one % to the terminal.
            case '%':
            {
                terminal_putchar('%');
                str++;
                break;
            }

            //If the current character is a 'c' the next argument in the va_arg list is a character
            case 'c':
            {
                //Print the character to the terminal and increment the str.
                terminal_putchar(va_arg(args, int));
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

            case 'x':
            {
                // Get the next argument from the va_list as an unsigned integer.
                int num = va_arg(args, int);
                // Calculate the number of digits in the hexadecimal representation.
                int num_digits = 0;
                int temp = num;
                do 
                {
                    num_digits++;
                    temp /= 16;
                } 
                while (temp != 0);
                // Create a buffer to store the hexadecimal representation of the number.
                char hex_buffer[9] = {0};
                // Convert each digit of the number to a hexadecimal character.
                for (int i = num_digits - 1; i >= 0; i--) 
                {
                    int digit = (num >> (4 * i)) & 0xF;
                    if (digit < 10) 
                    {
                        hex_buffer[num_digits - i - 1] = '0' + digit;
                    } 
                    else 
                    {
                        hex_buffer[num_digits - i - 1] = 'a' + (digit - 10);
                    }
                }
                // Print the hexadecimal string to the terminal.
                for (int i = 0; i < num_digits; i++) 
                {
                    terminal_putchar(hex_buffer[i]);
                }
                // Move on to the next character in the format string.
                str++;
                break;
            }
        }
    }
    //Calls the va_end function that frees any resources associated with the list.
    va_end(args);
}

