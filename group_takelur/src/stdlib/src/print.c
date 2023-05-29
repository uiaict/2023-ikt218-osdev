#include <stdarg.h> // for va_list
#include "monitor.h"
#include "print.h"


// Reverses a string
void reverse(char* str, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        // Swap characters
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        
        start++;
        end--;
    }
}

// Convert integer to ascii string (inspired from: https://www.geeksforgeeks.org/implement-itoa/)
void itoa(int value, char *str, int base)
{
    // Case for value being zero
    if (value == 0)
    {
        str[0] = '0';  // Set the first character in the string to '0'
        str[1] = '\0'; // Set the second character in the string to the null terminator
        return;        // Return from the function
    }

    int i = 0;           // Initialize the index for the resulting string
    int is_negative = 0; // Initialize flag to check if value is negative

    // If the base is decimal and the value is less than 0
    if (value < 0 && base == 10)
    {
        is_negative = 1; // Indicate that the value is negative
        value = -value;  // Convert the value to positive
    }

    // Process the value
    while (value != 0)
    {
        // Get the least significant digit
        int digit = value % base;
        
        // If digit is more than 9, it should be a letter
        str[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';

        value /= base; // Get the next digit
    }

    // If value was negative, append '-'
    if (is_negative)
    {
        str[i++] = '-'; 
    }

    str[i] = '\0'; // End the string

    // Reverse the string since we've formed the number from least to most significant digit
    reverse(str, i);
}

// Function to print an integer.
void print_int(int num) {
    char buffer[50]; // Ensure the buffer is large enough.
    itoa(num, buffer, 10); // Convert integer to string.
    monitor_write(buffer, 0, 15); // Print the string.
}


// Function to print a string.
void print_str(char* str) {
    // Use monitor_write() to print a string.
    monitor_write(str, 0, 15); // bg_color = 0 (black), fg_color = 15 (white)
}

// Function to print a character
void print_char(char c) {
    // Use monitor_put() to print a single character.
    monitor_put(c, 0, 15); // bg_color = 0 (black), fg_color = 15 (white)
}

void printf(char *str, ...)
{
    
    va_list args;           // Declare list of arguments
    va_start(args, str);    // Init list of arguments

    // Go through the string, print as necessary
    while (*str != '\0') {
        if (*str == '%') { // If there is a format specifier
            str++;
            switch (*str) {
                case 'd': { // Format for decimal integer
                    int num = va_arg(args, int);
                    print_int(num);
                    break;
                }
                case 's': { // Format for string
                    char *s = va_arg(args, char *);
                    print_str(s);
                    break;
                }
                case 'c': { // Format for character
                    char c = va_arg(args, int); // Char is promoted to int when passed through the list
                    print_char(c);
                    break;
                }
                case '%': // Format for literal '%'
                    print_char('%');
                    break;
                default:
                    // Print both the '%' and the following character
                    print_char('%');
                    print_char(*str);
                    break;
            }
        } else {
            print_char(*str);
        }
        str++;
    }

    va_end(args);   // Clean up the list of arguments
}