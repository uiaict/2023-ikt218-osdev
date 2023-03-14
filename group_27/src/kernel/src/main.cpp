
#include "system.h"
#include "common.h"
#include "monitor.h"

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
// Code from https://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C

void clear_terminal(void) 
{
	terminal_row = 0;  // start in the upper left corner in the canvas/terminal
	terminal_column = 0; // start in the upper left corner
	terminal_color = 7;     // 7 = VGA_COLOR_LIGHT_GREY
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {   // looping through terminal window 
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x; // find cursor position 
			terminal_buffer[index] = vga_entry(' ', terminal_color); // coloring every bit 
		}
	}
}

void write_to_terminal(char word[50])
{
    uint8_t (*fb)[80][2] = (uint8_t (*)[80][2]) 0xb8000;

    int wordlen = 0;

    while(word[wordlen] != '\0' ){
        wordlen++;
    }

    for(int i = 0; i < wordlen; i++){
        fb[4][i][0] = word[i];
    }
}
 
void kernel_main(void) 
{
	clear_terminal();

    write_to_terminal("Hello World");
}