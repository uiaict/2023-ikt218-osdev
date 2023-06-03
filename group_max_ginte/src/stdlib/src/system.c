#include "system.h"
#include "stdarg.h"
#include "memory.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_SIZE 4    

#define NEWLINE '\n'
#define TAB '\t'

volatile char *video = (volatile char*)0xB8000;     // Memory address of beginning of text mode with color
int x = 0;                                          // Current screen column 
int y = 0;                                          // Current screen row


char *strcpy(char *dest, const char *src)
{
    int i = 0;
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

char* strrev(char* str)
{
    char c;
    int length = 0;
    int i = 0;

    while(str[length] != '\0')
    {
        length++;
    }

    while(i < length/2)
    {
        c = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = c;
        i++;
    }
    return str;
}

char* itoa(int i, char* str, int base)
{
    char* string = str;
    int digit = 0;
    int sign = 0;

    if (i < 0)
    {
        sign = 1;
        i = -i;
    }

    while (i)
    {
        digit = i % base;
        *string = (digit > 9) ? ('A' + digit - 10) : '0' + digit;
        i /= base;
        string++;
    }

    if(sign)
    {
        *string++ = '-';
    }

    *string = '\0';
    strrev(str);
    return str;
}


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

    va_list vl;
    va_start(vl, format);
    char buff[100] = {0};
    char tmp[20];
    char* str_arg;

    int length = 0;                                 // Amount of characters printed

    while( *format != 0 )
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'c': {
                buff[0] = (char)va_arg(vl, int);

                printf(buff);
                format++;
                memset(buff, 0, 100);
                break;
            }
            case 's': {
                str_arg = va_arg(vl, char*);
                strcpy(buff, str_arg);

                printf(buff);
                format++;
                memset(buff, 0, 100);
                break;
            }
            case 'd': {
                itoa(va_arg(vl, int), tmp, 10);
                strcpy(buff, tmp);
                memset(tmp, 0, 20);

                printf(buff);
                format++;
                memset(buff, 0, 100);
                break;
            }
            case 'x': {
                itoa(va_arg(vl, int), tmp, 16);
                strcpy(buff, tmp);
                memset(tmp, 0, 20);

                printf(buff);
                format++;
                memset(buff, 0, 100);
                break;
            }
            default:
                break;
            }
        }

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

        if (y >= VGA_HEIGHT)
        {
            // "Scrolling" functionality
            video = (volatile char*)0xB8000;
            memset(video, 0, 80*25*2);
            y=0;    
        }
    }

    return length;
}
