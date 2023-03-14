#include "system.h"
#include "stdio.h"
#include "stdarg.h"
#define VIDEO_MEMORY_ADDRESS 0xB8000
#define VIDEO_MEMORY_SIZE 80 * 25 * 2 // 80 columns x 25 rows x 2 bytes per character


void clear_screen()
{
    volatile char *video = (volatile char *)VIDEO_MEMORY_ADDRESS;
    for (int i = 0; i < VIDEO_MEMORY_SIZE; i += 2)
    {
        // Set the character to space (0x20) and attribute to black on black (0x00)
        *video++ = 0x20;
        *video++ = 0x00;
    }
}

void print_char(char c, unsigned char color, unsigned int position)
{
    char *video_memory = (char *)VIDEO_MEMORY_ADDRESS;
    video_memory[position * 2] = c;
    video_memory[position * 2 + 1] = color;
}

unsigned int printk(unsigned int position, const char *format, ...)
{
    va_list args;
    va_start(args, format);


    char c;

    while ((c = *format++))
    {
        if (c == '%')
        {
            c = *format++;
            switch (c)
            {
            case 'd':
            {
                int arg = va_arg(args, int);
                char buf[32];
                itoa(arg, buf, 10);
                for (int i = 0; buf[i]; i++)
                {
                    print_char(buf[i], 0x0F, position++);
                }
                break;
            }
            case 's':
            {
                char *arg = va_arg(args, char *);
                while (*arg)
                {
                    print_char(*arg++, 0x0F, position++);
                }
                break;
            }
            case 'c':
            {
                char arg = (char)va_arg(args, int);
                print_char(arg, 0x0F, position++);
                break;
            }
            }
        }
        else if (c == '\n')
        {                                        // check for newline character
            position = (position / 80 + 1) * 80; // move to the start of the next line
        }
        else
        {
            print_char(c, 0x0F, position++);
        }
    }

    va_end(args);
    return position;
}

void reverse(char *str, int length)
{
    for (int i = 0; i < length / 2; i++)
    {
        char tmp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = tmp;
    }
}

void itoa(int value, char *str, int base)
{
    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int i = 0;
    int is_negative = 0;

    if (value < 0 && base == 10)
    {
        is_negative = 1;
        value = -value;
    }

    while (value != 0)
    {
        int digit = value % base;
        str[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
        value /= base;
    }

    if (is_negative)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);
}