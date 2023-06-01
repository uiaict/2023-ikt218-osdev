#include "system.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "time.h"
#include <stdint.h>
#include <limits.h>
#include <stdarg.h>


void *memset(void *s, int c, size_t n) {
    unsigned char *p = (unsigned char *)s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

//----------------------------------MOLLOYSTART------------------------------------------------------------

// The VGA framebuffer starts at 0xB8000.
uint16_t *video_memory = (uint16_t *)0xB8000;
// Stores the cursor position.
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;



// Updates the hardware cursor.
static void move_cursor()
{
    // The screen is 80 characters wide...
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{

    // Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(cursor_y >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
            video_memory[i] = blank;
        }
        // The cursor should now be on the last line.
        cursor_y = 24;
    }
}

// Writes a single character out to the screen.
void monitor_put(char c)
{
    // The background colour is black (0), the foreground is white (15).
    uint8_t backColour = 0;
    uint8_t foreColour = 15;

    // The attribute byte is made up of two nibbles - the lower being the 
    // foreground colour, and the upper the background colour.
    uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    uint16_t attribute = attributeByte << 8;
    uint16_t *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    // Scroll the screen if needed.
    scroll();
    // Move the hardware cursor.
    move_cursor();

}


void monitor_clear()
{
    // Make an attribute byte for the default colours
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        video_memory[i] = blank;
    }

    // Move the hardware cursor back to the start.
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(char *c)
{
    int i = 0;
    while (c[i])
    {
        monitor_put(c[i++]);
    }
}

//-----------------------------------------------MOLLOYFERDIG------------------------------------------------------------
int printf(const char *string, ...)
    {
        volatile char *video = (volatile char*)0xB8000;
        while( *string != 0 )
        {
            *video++ = *string++;
            *video++ = 0x0F;
        }
    }

//--------------------------finn kilde på det under--------------------------------------------------------

#define VIDEO_MEMORY_ADDRESS 0xB8000  // Define constant for the memory address of video memory
#define VIDEO_MEMORY_SIZE 80 * 25 * 2 // Define constant for the size of video memory in bytes (80 columns x 25 rows x 2 bytes per character)

void print_char(char c, unsigned char color, unsigned int position)
{
    char *video_memory = (char *)VIDEO_MEMORY_ADDRESS; // Create a pointer to the video memory
    video_memory[position * 2] = c;                    // Set the character at the specified position in video memory
    video_memory[position * 2 + 1] = color;            // Set the attribute at the specified position in video memory
}

void printt(const char *format, ...)
{
    static unsigned int position = 0; // Initialize the previous position to 0
    va_list args;           // Declare a list of arguments
    va_start(args, format); // Start the list of arguments at the format parameter

    if (position >= 80 * 25){
        for (unsigned int i = 0; i < (80 * 24); ++i) {
            ((char*)VIDEO_MEMORY_ADDRESS)[i * 2] = ((char*)VIDEO_MEMORY_ADDRESS)[(i + 80) * 2];
            ((char*)VIDEO_MEMORY_ADDRESS)[i * 2 + 1] = ((char*)VIDEO_MEMORY_ADDRESS)[(i + 80) * 2 + 1];
        }
        for (unsigned int i = 80 * 24; i < 80 * 25; ++i) {
            ((char*)VIDEO_MEMORY_ADDRESS)[i * 2] = ' ';
            ((char*)VIDEO_MEMORY_ADDRESS)[i * 2 + 1] = 0x0F;
        }
        position -= 80;
    }

    char c; // Declare a character to hold the current character in the format string

    while ((c = *format++)) // Loop over every character in the format string
    {
        if (c == '%') // If the current character is a formatting character
        {
            c = *format++; // Get the next character to determine the type of formatting

            switch (c) // Switch on the formatting character
            {
            case 'd': // If the format is for an integer
            {
                int arg = va_arg(args, int); // Get the integer argument from the list of arguments
                char buf[32];                // Declare a buffer to hold the integer as a string
                itoa(arg, buf, 10);          // Convert the integer to a string using base 10
                for (int i = 0; buf[i]; i++) // Loop over every character in the string
                {
                    print_char(buf[i], 0x0F, position++); // Print the character at the current position in the string and increment the position
                }
                break;
            }
            case 's': // If the format is for a string
            {
                char *arg = va_arg(args, char *); // Get the string argument from the list of arguments
                while (*arg)                      // Loop over every character in the string
                {
                    print_char(*arg++, 0x0F, position++); // Print the character at the current position in the string and increment the position
                }
                break;
            }
            case 'c': // If the format is for a character
            {

                char arg = (char)va_arg(args, int); // Get the character argument from the list of arguments
                if (arg == 0x0E) //Backslash
                {
                    if (position > 0)
                    {
                        position -= 1;// Set the character to space (0x20) and attribute to black on black (0x00)
                        print_char(0x20, 0x00, position);
                    }
                    break;
                }
                else{
                print_char(arg, 0x0F, position++);  // Print the character at the current position in the string and increment the position
                break;
            }
                case 'x':
                {
                    int arg = va_arg(args, int); // Get the integer argument from the list of arguments
                    char buf[32];                // Declare a buffer to hold the integer as a string
                    itoa(arg, buf, 16);          // Convert the integer to a string using base 16
                    for (int i = 0; buf[i]; i++) // Loop over every character in the string
                    {
                        print_char(buf[i], 0x0F, position++); // Print the character at the current position in the string and increment the position
                    }
                    break;
                }
            }
            }
        }
        else if (c == '\n') // If the current character is a newline character
        {
            position = (position / 80 + 1) * 80; // Move the position to the start of the next line by adding 80 minus the current column to the current position
        }
        else // If the current character is not a formatting character or a newline character
        {
            print_char(c, 0x0F, position++); // Print the character at the current position in the string and increment the position
        }
    }

    va_end(args);    // End the list of arguments
    //return position; // Return the final position after printing the formatted string
    scroll();
    move_cursor();
}


void reverse(char *str, int length)
{
    for (int i = 0; i < length / 2; i++) // Loop over every character in the first half of the string
    {
        char tmp = str[i];            // Store the current character in a temporary variable
        str[i] = str[length - i - 1]; // Replace the current character with its corresponding character in the second half of the string
        str[length - i - 1] = tmp;    // Replace the corresponding character in the second half of the string with the temporary variable
    }
}


void itoa(int value, char *str, int base)
{
    if (value == 0) // If the value is zero
    {
        str[0] = '0';  // Set the first character in the string to '0'
        str[1] = '\0'; // Set the second character in the string to the null terminator
        return;        // Return from the function
    }
    int i = 0;           // Declare a variable to hold the current index in the string
    int is_negative = 0; // Declare a flag to indicate if the value is negative

    if (value < 0 && base == 10) // If the value is negative and the base is 10
    {
        is_negative = 1; // Set the flag to indicate that the value is negative
        value = -value;  // Make the value positive for the conversion
    }

    while (value != 0) // Loop until the value is zero
    {
        int digit = value % base;                                  // Get the least significant digit of the value in the specified base
        str[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0'; // Convert the digit to a character and add it to the string, either as a number or a letter if the digit is greater than 9
        value /= base;                                             // Divide the value by the base to remove the least significant digit
    }

    if (is_negative) // If the value was negative
    {
        str[i++] = '-'; // Add a negative sign to the string
    }

    str[i] = '\0'; // Add the null terminator to the end of the string

    reverse(str, i); // Reverse the string in place
}











