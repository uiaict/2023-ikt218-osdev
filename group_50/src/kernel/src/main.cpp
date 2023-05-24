#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "terminal.h"

// Define VGA text mode buffer
// Pointer to the memory-mapped VGA buffer that represents the screen
volatile uint16_t* const VGA_BUFFER = (uint16_t*) 0xB8000; 

// Constants to define the dimensions of the text module
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

// Initialize terminal
void terminal_init() {
    
	for (size_t i = 0; i < VGA_HEIGHT; i++) {
        
		for (size_t j = 0; j < VGA_WIDTH; j++) {
			const size_t index = i * VGA_WIDTH + j; // Calculate index of current character
            VGA_BUFFER[index] = ' ' | 0x0700; 		// Write a white character with black background and white foreground to the buffer
        }
    }
}

// Print string to terminal
void terminal_write(const char* str) {
    
	size_t index = 0; // Index to keep track of current character

    while (str[index]) { // Loop until null
        
		const size_t row = index / VGA_WIDTH; // Calculate row of current character
        const size_t col = index % VGA_WIDTH; // Calculate column of current character
        const size_t vga_index = row * VGA_WIDTH + col; // Calculate index in VGA buffer for current character
        
		VGA_BUFFER[vga_index] = ((uint16_t) str[index]) | 0x0700; // Write current character to the buffer
        index++;
    }
}

size_t terminal_row = 0;
size_t terminal_col = 0;

void terminal_write_char(char c) {
    
    if (c == '\b') { // Backspace
        if (terminal_col > 0) {
            terminal_col--;
        } 
        else if (terminal_row > 0) {
            terminal_row--;
            terminal_col = VGA_WIDTH - 1;
        }
        
        const size_t index = terminal_row * VGA_WIDTH + terminal_col;
        VGA_BUFFER[index] = ((uint16_t) ' ') | 0x0700; // Overwrite with a space
    } 
    else if (c == '\n') { // Newline
        terminal_col = 0;
        terminal_row++;
    } 
    else { // Regular character
        const size_t index = terminal_row * VGA_WIDTH + terminal_col;
        VGA_BUFFER[index] = ((uint16_t) c) | 0x0700; // Write current character to the buffer

        terminal_col++;

        if (terminal_col == VGA_WIDTH) {
            terminal_col = 0;
            terminal_row++;
        }
    }
    if (terminal_row == VGA_HEIGHT) {
        terminal_init(); 
        terminal_row = 0;
        terminal_col = 0;
    }
}

// Define entry point in asm to prevent C++ mangling
extern "C"{
    void kernel_main();
}

void kernel_main()
{
    terminal_init();
    terminal_write("Hello World");
    
    asm volatile("int $0x3");
    asm volatile("int $0x4");
    //asm volatile("int $0x5");

   terminal_init();
   while(true){};
}
