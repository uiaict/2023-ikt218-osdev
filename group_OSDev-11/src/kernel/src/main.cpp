#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"

// Constants for VGA text mode buffer
static volatile uint16_t* const VGA_TEXT_BUFFER = (uint16_t*) 0xB8000; 
const size_t TEXT_WIDTH = 80;
const size_t TEXT_HEIGHT = 25;

// Initialize terminal by filling the VGA buffer with blank spaces and black background
void initialize_terminal() {
    for (size_t row = 0; row < TEXT_HEIGHT; row++) {
        for (size_t col = 0; col < TEXT_WIDTH; col++) {
            const size_t index = row * TEXT_WIDTH + col;
            VGA_TEXT_BUFFER[index] = ' ' | 0x0700; 
        }
    }
}

// Function to write a string to the terminal
void write_to_terminal(const char* str) {
    size_t position = 0; 

    while (str[position]) {
        const size_t row = position / TEXT_WIDTH; 
        const size_t col = position % TEXT_WIDTH;
        const size_t vga_index = row * TEXT_WIDTH + col;

        VGA_TEXT_BUFFER[vga_index] = str[position] | 0x0700; 
        position++;
    }
}

// Entry point for kernel defined in asm to avoid C++ name mangling
extern "C"{
    void main_kernel();
}

void main_kernel()
{
    initialize_terminal();
    write_to_terminal("Hello World");
}
