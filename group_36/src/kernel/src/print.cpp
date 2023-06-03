#include "print.h"
#include <stddef.h>
#include <stdint.h>

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
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
	if (c == '\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	} else {
	
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT) {
				terminal_row = 0;
			}
		}
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void printf(const char* data) 
{
	terminal_write(data, strlen(data));
}

void print_uint8(uint8_t scancode) {
    char buffer[12];  // Buffer for up to 10 digits plus null terminator
    uint8_t n = scancode;
    int i = 0;

    // Handle 0 explicitly (as the loop below doesn't do that)
    if (n == 0) {
        buffer[i++] = '0';
    }
    else {
        // Convert number to string (in reverse order)
        while (n > 0) {
            buffer[i++] = '0' + n % 10;
            n /= 10;
        }

        // Reverse the string to get it in the correct order
        for (int j = 0; j < i / 2; ++j) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
    }

    buffer[i] = '\0';  // Null-terminate the string

    printf(buffer);
}

void print_int(int n) {
    char buffer[12];  // Buffer for up to 10 digits plus null terminator
    int i = 0;

    // Handle 0 explicitly (as the loop below doesn't do that)
    if (n == 0) {
        buffer[i++] = '0';
    }
    else {
        // Convert number to string (in reverse order)
        while (n > 0) {
            buffer[i++] = '0' + n % 10;
            n /= 10;
        }

        // Reverse the string to get it in the correct order
        for (int j = 0; j < i / 2; ++j) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
    }

    buffer[i] = '\0';  // Null-terminate the string

    printf(buffer);
}

char hex_char(uint32_t val) {
    val &= 0xF; // keep only lowest 4 bits
    if (val <= 9) {
        return '0' + val;
    } else {
        return 'A' + (val - 10);
    }
}

void print_hex(uint32_t d)
{
    printf("0x");
    for(int i = 28; i >= 0; i-=4)
    {
        terminal_putchar(hex_char(d>>i));
    }

}
