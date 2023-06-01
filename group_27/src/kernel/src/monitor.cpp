// monitor.c -- Defines functions for writing to the monitor.
//             heavily based on Bran's kernel development tutorials,
//             but rewritten for JamesM's kernel tutorials.

#include "monitor.h"
#include "commander.h"
#include <cstddef>
#include <libc/system.h>

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
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
uint16_t *video_memory = (uint16_t *)0xB8000;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

// Scrolls the text on the screen up by one line.
static void scroll()
{

    // Get a space character with the default colour attributes.
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(terminal_row >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            terminal_buffer[i] = terminal_buffer[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24*80; i < 25*80; i++)
        {
    
            terminal_buffer[i] = blank;
        }
        // The cursor should now be on the last line.
        terminal_row = 24;
    }
}


// Updates the hardware cursor.
static void move_cursor()
{
    // The screen is 80 characters wide...
    uint16_t pos = terminal_row * 80 + terminal_column;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void monitor_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = video_memory;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void monitor_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void monitor_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void show_cursor() {
    monitor_putentryat('_', terminal_color, terminal_column, terminal_row);
}
void hide_cursor() {
    monitor_putentryat(' ', terminal_color, terminal_column, terminal_row);
}
void set_prefix(char* c) {
    printf(c);
}

void monitor_put(char c, bool isKeypress) 
{
    hide_cursor();

	switch (c)
	{
	case '\n':                  // ENTER
		terminal_column = 0;
        terminal_row++;
        scroll();
        show_cursor();
        if (isKeypress) {
            run_command();
        }
		return;
    case '\016':                // BACKSPACE
        if (terminal_column <= 2) {
            show_cursor();
            return;
        }
        terminal_column--;
        decrease_buffer();
        monitor_putentryat(' ', terminal_color, terminal_column, terminal_row);
        show_cursor();
        return;
    default:
        //increase_buffer();
	    monitor_putentryat(c, terminal_color, terminal_column, terminal_row);
	    if (++terminal_column == VGA_WIDTH) {
		    terminal_column = 0;
		    if (++terminal_row == VGA_HEIGHT)
			    terminal_row = 0;
	    }
	}
    if (isKeypress) {
        increase_buffer(c);
    }

    show_cursor();
}
 
void monitor_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		monitor_put(data[i], false);
    
    // Scroll the screen if needed.
    scroll();
    // Move the hardware cursor.
    move_cursor();
}
 
void monitor_writestring(const char* data) 
{
	monitor_write(data, strlen(data));
}


// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
    // Make an attribute byte for the default colours
    uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        terminal_buffer[i] = blank;
    }

    // Move the hardware cursor back to the start.
    terminal_row = -1;
    terminal_column = 0;
    move_cursor();
    show_cursor();
}

void monitor_write_hex(uint32_t n)
{
    int32_t tmp;
    char* item = "0x";

    monitor_write(item, strlen(item));

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            monitor_put (tmp-0xA+'a', false);
        }
        else
        {
            noZeroes = 0;
            monitor_put( tmp+'0', false);
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        monitor_put (tmp-0xA+'a', false);
    }
    else
    {
        monitor_put (tmp+'0', false);
    }

}

void monitor_write_dec(uint32_t n)
{

    if (n == 0)
    {
        monitor_put('0', false);
        return;
    }

    int32_t acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc % 10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    monitor_write(c2, strlen(c2));

}

void print_logo() {
printf(
"                         _________ _______    _______  _______\n"
"                |\\     /|\\__   __/(  ___  )  (  ___  )(  ____ \\\n"
"                | )   ( |   ) (   | (   ) |  | (   ) || (    \\/\n"
"                | |   | |   | |   | (___) |  | |   | || (_____ \n"
"                | |   | |   | |   |  ___  |  | |   | |(_____  )\n"
"                | |   | |   | |   | (   ) |  | |   | |      ) |\n"
"                | (___) |___) (___| )   ( |  | (___) |/\\____) |\n"
"                (_______)\\_______/|/     \\|  (_______)\\_______)\n"
"            By Markus Hagli, Charlotte Thorjussen, Nikolai Eidsheim");
}