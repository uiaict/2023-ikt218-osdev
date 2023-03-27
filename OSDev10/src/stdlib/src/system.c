#include "system.h"

#define VIDEO_BUFFER 0xB8000
#define VIDEO_HEIGHT 30
#define VIDEO_WIDTH 100

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_LIGHT_CYAN = 11,
	
};


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}





void clear_screen() 
{
    const uint8_t color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;
    
    for (int i = 0; i < VIDEO_HEIGHT * VIDEO_WIDTH; i++) 
    {
        *video++ = vga_entry(' ', color);
    }
}

int printf(const char *format, ...)
{
    const uint8_t color = vga_entry_color(VGA_COLOR_LIGHT_CYAN,VGA_COLOR_BLACK);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;

    for (const char* current_char = format; *current_char != '\0'; current_char++)
    {
        *video++ = vga_entry(*current_char, color);
    }

    return 1;
}


