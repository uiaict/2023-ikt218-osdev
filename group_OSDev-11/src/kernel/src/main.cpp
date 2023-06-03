#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "terminal.h"

// The VGA buffer's memory location, acting as the screen
volatile uint16_t* const VGA_TEXT_BUFFER = (uint16_t*) 0xB8000;

// Terminal dimensions in VGA text mode
const size_t VGA_TEXT_WIDTH = 80;
const size_t VGA_TEXT_HEIGHT = 25;

// Keeping track of the current position within the terminal
size_t terminal_row = 0;
size_t terminal_col = 0;

// Function to reset terminal, by filling it with spaces
void initialize_terminal() {
    // Loop over all rows and columns, setting each position to a space character
    for (size_t y = 0; y < VGA_TEXT_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_TEXT_WIDTH; x++) {
            const size_t index = y * VGA_TEXT_WIDTH + x;
            VGA_TEXT_BUFFER[index] = ' ' | 0x0700; // Write a space character with black background and white foreground
        }
    }
}

// Outputs a string to the terminal
void write_to_terminal(const char* str) {
    size_t index = 0;
    // Iterate through each character of the string until null character
    while (str[index]) {
        const size_t row = index / VGA_TEXT_WIDTH;
        const size_t col = index % VGA_TEXT_WIDTH;
        const size_t vga_index = row * VGA_TEXT_WIDTH + col;
        // Write each character with black background and white foreground
        VGA_TEXT_BUFFER[vga_index] = ((uint16_t) str[index]) | 0x0700;
        index++;
    }
}

// Outputs a single character to the terminal, taking into account special characters
void output_char_to_terminal(char c) {
    if (c == '\b') { // Backspace character handling
        // Move the cursor backwards, considering it might be at the beginning of a line
        if (terminal_col > 0) {
            terminal_col--;
        } else if (terminal_row > 0) {
            terminal_row--;
            terminal_col = VGA_TEXT_WIDTH - 1;
        }
        const size_t index = terminal_row * VGA_TEXT_WIDTH + terminal_col;
        VGA_TEXT_BUFFER[index] = ((uint16_t) ' ') | 0x0700; // Replace the character at the cursor with a space
    } else if (c == '\n') { // Newline character handling
        terminal_col = 0;
        terminal_row++;
    } else { // Other characters
        const size_t index = terminal_row * VGA_TEXT_WIDTH + terminal_col;
        VGA_TEXT_BUFFER[index] = ((uint16_t) c) | 0x0700;
        terminal_col++;
        if (terminal_col == VGA_TEXT_WIDTH) {
            terminal_col = 0;
            terminal_row++;
        }
    }
    // If the cursor has reached the end of the terminal, clear the terminal and reset the cursor
    if (terminal_row == VGA_TEXT_HEIGHT) {
        initialize_terminal();
        terminal_row = 0;
        terminal_col = 0;
    }
}

// Main function declaration, using extern to prevent C++ name mangling
extern "C"{
    void main_kernel();
}

// Main function definition
void main_kernel()
{
    // Initialize terminal and display a string
    initialize_terminal();
    write_to_terminal("Hello, World!");

    // Trigger software interrupts
    asm volatile("int $0x3");
    asm volatile("int $0x4");

    // Clear terminal and enter an infinite loop
    initialize_terminal();
    while(true){};
}
