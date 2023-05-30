#include "include/terminal.h"

// Source: https://wiki.osdev.org/Bare_Bones Fetched: 15.03.2023

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		  if (data[i] == '\n') {
            // Move to the beginning of the next line
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                terminal_row = 0;
        } else {
            terminal_putchar(data[i]);
	}
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

int printf(const char* __restrict__ format, ...) {
    // TODO %d and alot of formatting is missing!
    // This you can implement yourtself!
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
 
	while (*format != '\0') {
		size_t maxrem = VGA_WIDTH - written;
 
		if (format[0] != '%' || format[1] == '%') {
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			terminal_write(format, amount);
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			terminal_putchar(c);
			written++;
		} else if (*format == 's') {
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			terminal_writestring(str);
			written += len;
		} else if (*format == 'd') {
            format++;
            int num = va_arg(parameters, int);
            char buffer[20];
            int i = 0;
            if (num == 0) {
                buffer[i++] = '0';
            } else if (num < 0) {
                buffer[i++] = '-';
                num = -num;
            }
            while (num != 0) {
                buffer[i++] = num % 10 + '0';
                num /= 10;
            }
            while (i > 0) {
                if (maxrem < 1) {
                    // TODO: Set errno to EOVERFLOW.
                    return -1;
                }
                terminal_putchar(buffer[--i]);
                written++;
            }
        } else if (*format == 'x') {
            format++;
            unsigned int num = va_arg(parameters, unsigned int);
            char buffer[20];
            int i = 0;
            if (num == 0) {
                buffer[i++] = '0';
            }
            while (num != 0) {
                int rem = num % 16;
                if (rem < 10) {
                    buffer[i++] = rem + '0';
                } else {
                    buffer[i++] = rem - 10 + 'a';
                }
                num /= 16;
            }
            while (i > 0) {
                if (maxrem    < 1) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            terminal_putchar(buffer[--i]);
            written++;
			}

		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			// if (!print(format, len))
				// return -1;
			written += len;
			format += len;
		}
	}
 
	va_end(parameters);
	return written;
}