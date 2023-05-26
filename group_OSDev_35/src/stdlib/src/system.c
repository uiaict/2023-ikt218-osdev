#include "system.h"
#include <stdarg.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Function to clear the terminal
void clear_terminal() {

    // Get a pointer to the VGA memory address
    static volatile uint16_t *vga_buffer = (volatile uint16_t*)0xB8000;

    // Loop through each character cell and set it to a space
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = (uint16_t) ' ' | 0x0700;
        }
    } 
}

// Function to print logo presentation
void print_logo() {
    printf("                   _    _   _                 ____     _____ \n");
    printf("                  | |  | | (_)     /\\        / __ \\   / ____|\n");
    printf("                  | |  | |  _     /  \\      | |  | | | (___  \n");
    printf("                  | |  | | | |   / /\\ \\     | |  | |  \\___ \\ \n");
    printf("                  | |__| | | |  / ____ \\    | |__| |  ____) |\n");
    printf("                   \\____/  |_| /_/    \\_\\    \\____/  |_____/ \n");
    printf("\n");

}


void itoa(int value, char *str, int base)
{
    char *ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;

    if (base < 2 || base > 36)
    {
        *str = '\0';
        return;
    }

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
    } while (value);

    if (tmp_value < 0)
    {
        *ptr++ = '-';
    }

    *ptr-- = '\0';

    while (ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}


int printf(const char *format, ...)
{
    va_list arg;
    static volatile char *output_buffer = (volatile char*)0xB8000;
    static int pos = 0;
    char buf[20];  // buffer for number to string conversion
    const char *s;

    va_start(arg, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            switch (*(++format))
            {
                case 'i':
                    itoa(va_arg(arg, int), buf, 10);  // convert int to string
                    s = buf;
                    while (*s != '\0')
                    {
                        if (*s == '\n')
                        {
                            pos += 2 * (VGA_WIDTH - (pos / 2) % VGA_WIDTH);
                        }
                        else
                        {
                            *(output_buffer + pos++) = *s++;
                            *(output_buffer + pos++) = 0x0F;
                        }
                    }
                    break;
                case 's':
                    s = va_arg(arg, const char *);
                    while (*s != '\0')
                    {
                        if (*s == '\n')
                        {
                            pos += 2 * (VGA_WIDTH - (pos / 2) % VGA_WIDTH);
                        }
                        else
                        {
                            *(output_buffer + pos++) = *s++;
                            *(output_buffer + pos++) = 0x0F;
                        }
                    }
                    break;
                default:
                    *(output_buffer + pos++) = *format;
                    *(output_buffer + pos++) = 0x0F;
                    break;
            }
            format++;
        }
        else
        {
            if (*format == '\n')
            {
                pos += 2 * (VGA_WIDTH - (pos / 2) % VGA_WIDTH);
                format++;
            }
            else
            {
                *(output_buffer + pos++) = *format++;
                *(output_buffer + pos++) = 0x0F;
            }
        }
    }

    va_end(arg);

    return 0;
}
