#include "system.h" // Include system header file
//#include "stdio.h"  // Include standard input/output header file
#include "stdarg.h" // Include standard argument header file

#define VIDEO_MEMORY_ADDRESS 0xB8000  // Define constant for the memory address of video memory
#define VIDEO_MEMORY_SIZE 80 * 25 * 2 // Define constant for the size of video memory in bytes (80 columns x 25 rows x 2 bytes per character)

void clear_screen()
{
    volatile char *video = (volatile char *)VIDEO_MEMORY_ADDRESS; // Create a pointer to the video memory, making it volatile to avoid compiler optimizations
    for (int i = 0; i < VIDEO_MEMORY_SIZE; i += 2)                // Loop over every character in video memory
    {
        // Set the character to space (0x20) and attribute to black on black (0x00)
        *video++ = 0x20; // Set the character to space
        *video++ = 0x00; // Set the attribute to black on black
    }
}

void print_char(char c, unsigned char color, unsigned int position)
{
    char *video_memory = (char *)VIDEO_MEMORY_ADDRESS; // Create a pointer to the video memory
    video_memory[position * 2] = c;                    // Set the character at the specified position in video memory
    video_memory[position * 2 + 1] = color;            // Set the attribute at the specified position in video memory
}

void printk(const char *format, ...)
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

