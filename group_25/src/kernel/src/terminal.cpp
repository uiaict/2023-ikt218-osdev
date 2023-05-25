#include "terminal.h"
#include <stddef.h>
#include <stdint.h>

static size_t terminal_row;         // Selected terminal row
static size_t terminal_column;      // Selected terminal column
static uint16_t *terminal_buffer;   

static const size_t TERMINAL_WIDTH = 80; // Terminal width
static const size_t TERMINAL_HEIGHT = 25;// Terminal height

// Creates a VGA entry using character and color
static uint16_t vga_entry(unsigned char uc, uint8_t color){
	return (uint16_t) uc | (uint16_t) color << 8;
}

// Clear the terminal
void terminal_initialize(void){
	terminal_buffer = (uint16_t *) 0xB8000;
	terminal_column = 0;
	terminal_row = 0;

	for (size_t y = 0; y < TERMINAL_HEIGHT; y++){
		for (size_t x = 0; x < TERMINAL_WIDTH; x++) {
			terminal_buffer[y * TERMINAL_WIDTH + x] = vga_entry(' ', 0x07);
		}
	}
}

// Write to the terminal
void terminal_write(const char *data, size_t size){
	for (size_t i = 0; i < size; i++) {

        // Handle newlines
        if(vga_entry(static_cast<unsigned char>(data[i]), 0x07) == vga_entry('\n', 0x07)){
            terminal_column = 0;
            if (++terminal_row == TERMINAL_HEIGHT){
				terminal_row = 0;
			}
            continue;
        }
        
        // Write the character to terminal
	    terminal_buffer[terminal_row * TERMINAL_WIDTH + terminal_column] = vga_entry(static_cast<unsigned char>(data[i]), 0x07);
		
		// Move to next collumn and row if end of terminal is reached
		if (++terminal_column == TERMINAL_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == TERMINAL_HEIGHT){
                terminal_row = 0;
		    }
		}
	}
}