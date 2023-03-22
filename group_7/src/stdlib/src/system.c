#include <stdarg.h>
#include <stdbool.h>

#include "system.h"

/// @brief This function takes a string and a color and prints it to the screen.
/// @param colour Value from 0-15:
/// 0 : Black 
/// 1 : Blue
/// 2 : Green
/// 3 : Cyan
/// 4 : Red
/// 5 : Purple
/// 6 : Brown
/// 7 : Gray
/// 8 : Dark Gray
/// 9 : Light Blue
/// 10 : Light Blue
/// 11 : Light Cyan
/// 12 : Light Red
/// 13 : Light Purple
/// 14 : Yellow
/// 15 : White
/// @param string The string you want to display
void write_string( int colour, const char *string )
{
    static volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;

        if(video == (volatile char*)0xB8FA4)
            video = (volatile char*)0xB8000;
    }
}

/// @brief 
/// @param format 
/// @param  
/// @return 
int printf(const char* format, ...) {
	/// allows for infinte parameters!
    va_list variables;
    /// starts the list of inifinte parameters.
	va_start(variables, format);
    /// the buffer output, as of now = 25*80.
    char buffer[25*80] = { 0 };
    /// used if a variable consists of multiple characters, i.e. string or array.
    char tmp[50] = { 0 };
    /// number of printed characters
	int written = 0;
    // loop thorugh all parameters
	while (*format != '\0') 
    {
		if (*format == '\n')
        {
            format++;
            int next = 80 - written%80;
            for(int i = 0; i < next; i++)
            {
                buffer[written] = ' ';
                written++;
            }
        }
        if (*format == '%')
        // check the next character to determine what to do:
        {
            format++;
            switch (*format)
            {
            // If c is used as the option after %, we take that carecter and write it to the buffer
            case 'c':
                format++;
                char c = (char) va_arg(variables, int);
                buffer[written] = c;
                written++;
                break;
            // If s is used as the option after %, we retrive that string a compies it to the buffer at the position we currentliy are on.
            // The written variable gets incremented by the lengt of that string so it still is correct with the number of characters
            // in the buffer so far. At last the format string is incremented by one.
            case 's':
                const char* s = va_arg(variables, const char*);
                strcpy(&buffer[written], s);
                size_t len = strlen(s);
                written += len;
                format ++;
                break;

            // Not implemented yet.
            /*case 'i':
                format++;
                int i = va_arg(variables, int);

                break;*/

            // If double %, like %%, add %, to the buffer.
            case '%':
                format++;
                buffer[written] = '%';
                written++;
                break;
            
            default:
                break;
            }
        }
        else {
            // Else, if there are no %, all the caracters are just added to the buffer
            buffer[written] = *format;
            format++;
            written++;
        }
	}

    // Write_string writes the buffer to the terminal with the color green
    write_string(2, buffer);
 
	va_end(variables);
	return written;
}

/// @brief Copies strinf drom src to dest
/// @param dest Destination string
/// @param src  Source string
/// @return The destination string pointer
char *strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    return dest;
}

/// @brief Counts the lengt of a string
/// @param s string to find lengt of
/// @return string length
size_t strlen(const char *s)
{
    int count = 0;
    while (*s != '\0')
    {
        count ++;
        s++;
    }

    return count;
}

void clearScreen()
{
    char blank[25*80];
    for (int i = 0; i < 25*80; i++)
        blank[i] = " ";
    
    write_string(0, blank);
}