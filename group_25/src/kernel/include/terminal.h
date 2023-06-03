#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <system.h>

// Text color constants
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

// Screen constants
#define SCREEN_BUFFER 0xB8000
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

// Current position
static uint8_t terminal_row = 0;
static uint8_t terminal_column = 0;

void terminal_clear();
void terminal_newline();
void terminal_write_char(char c);
bool terminal_write(const char *str);
void terminal_print_title(bool full);
void terminal_newpage();

#endif