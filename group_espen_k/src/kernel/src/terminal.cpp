#include "terminal.h"
#include "system.h"
#include <cstddef>

/**
 * https://perara.notion.site/Lecture-3-CMake-Libc-and-the-Terminal-fa7d2cdb5fb34c1cad143bd1238dcdaf#533420a676c948569bdaa9065c0aea4f
 * https://wiki.osdev.org/Bare_Bones#Implementing_the_Kernel
 * https://wiki.osdev.org/Printing_To_Screen
 * 
*/

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_clear()
{
    const uint8_t color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;
    for(size_t i = 0; i < VIDEO_HEIGHT*VIDEO_WIDTH; i++)
    {
        video[i] = vga_entry(' ', color);
    }
	video_line = 0;
	video_column = 0;
}

void terminal_write_char(char c)
{
	const uint8_t color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
	uint16_t *video = (uint16_t*)VIDEO_BUFFER;
	uint16_t index = video_line * VIDEO_WIDTH + video_column;

	//Handle backspace
	if(c == '\b'){
		if(video_column > 0){
			video_column--;
			index--;
			video[index] = vga_entry(' ', color);
		}
		return;
	}

	//Handle newline
	if(c == '\n'){
		video_column = 0;
		if (video_line == VIDEO_HEIGHT)
			video_line = 0;
		else
			video_line++;
		return;
	}



	video[index] = vga_entry(c, color);
	video_column++;
	if (index == VIDEO_WIDTH)
	{
		video_line++;
		video_column = 0;
	}
	if (video_line == VIDEO_HEIGHT)
	{
		terminal_clear();
		video_line = 0;
		video_column = 0;
	}	

}


void terminal_write(const char *str)
{
	if(video_line >= VIDEO_HEIGHT){
		terminal_clear();
		video_line = 0;
	}
	uint32_t offset = video_line * VIDEO_WIDTH;
    const uint8_t color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
    size_t stringLenght = strlen(str);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;
    for(size_t i = 0; i < stringLenght; i++ )
    {
        video[i + offset] = vga_entry(str[i], color);
    }
	video_line++;
}