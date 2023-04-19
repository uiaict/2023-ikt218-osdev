
#include "system.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"

// Define VGA text mode buffer
// Pointer to the memory-mapped VGA buffer that represents the screen
volatile uint16_t* const VGA_BUFFER = (uint16_t*) 0xB8000; 

// Constants to define the dimensions of the text module
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25;

// Initialize terminal (fill VGA buffer with blank spaces and black background)
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

		VGA_BUFFER[vga_index] = str[index] | 0x0700; // Write current character to the buffer
        index++;
    }
}


// Define entry point in asm to prevent C++ mangling
extern "C"
{
    void kernel_main();
}

void kernel_main()
{
    terminal_init();
    terminal_write("Hello World");
}