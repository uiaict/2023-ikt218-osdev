#include "system.h"

/**
 * https://perara.notion.site/Lecture-3-CMake-Libc-and-the-Terminal-fa7d2cdb5fb34c1cad143bd1238dcdaf#533420a676c948569bdaa9065c0aea4f
 * https://wiki.osdev.org/Bare_Bones#Implementing_the_Kernel
 * https://wiki.osdev.org/Printing_To_Screen
 * 
*/

#define VIDEO_BUFFER 0xB8000
#define VIDEO_HEIGHT 25
#define VIDEO_WIDTH 80

/* Hardware text mode color constants. */
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

static uint8_t video_line = 0;

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

void clearTerminal()
{
    const uint8_t color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;
    for(size_t i = 0; i < VIDEO_HEIGHT*VIDEO_WIDTH; i++)
    {
        video[i] = vga_entry(' ', color);
    }
}


int printf(const char *format, ...)
{
	if(video_line >= VIDEO_HEIGHT){
		clearTerminal();
		video_line = 0;
	}
	uint32_t offset = video_line * VIDEO_WIDTH;
    const uint8_t color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
    size_t stringLenght = strlen(format);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;
    for(size_t i = 0; i < stringLenght; i++ )
    {
        video[i + offset] = vga_entry(format[i], color);
    }
	video_line++;
    return 1;
}