#include "terminal.h"
#include "system.h"
#include <cstddef>

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_clear(){
    uint16_t *screen = (uint16_t*)SCREEN_BUFFER;
	const uint8_t clear_color = vga_entry_color(VGA_COLOR_BROWN, VGA_COLOR_BLACK);
    for(size_t i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++){
        screen[i] = vga_entry(' ', clear_color);
    }
	terminal_column = 0;
	terminal_row = 0;
}

void terminal_write_char(char c){
	const uint8_t color = vga_entry_color(VGA_COLOR_BROWN,VGA_COLOR_BLACK);
	uint16_t *screen = (uint16_t*)SCREEN_BUFFER;
	uint16_t index = terminal_row * SCREEN_WIDTH + terminal_column;

	//Newline
	if(c == '\n' || terminal_column == SCREEN_WIDTH){
		terminal_newline();
		return;
	}

	//Backspace
	if(c == '\b'){
		if(terminal_column > 0){
			terminal_column--;
			index--;
			screen[index] = vga_entry(' ', color);
		}
		return;
	}

	// Write char
	terminal_column++;
	screen[index] = vga_entry(c, color);
}

void terminal_write(const char *str){
    size_t stringLenght = strlen(str);
    for(size_t i = 0; i < stringLenght; i++ ){
		terminal_write_char(str[i]);
    }
}

void terminal_newline(){
	terminal_column = 0;
	terminal_row++;
	if(terminal_row >= SCREEN_HEIGHT){
		terminal_clear();
		terminal_row = 0;
	}
}