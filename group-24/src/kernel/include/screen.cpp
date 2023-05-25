#include "screen.h"

// Function to unset the screen by shifting the content up
void unset_screen() {
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = vidmem[i+160];
        vidmem[i+1] = vidmem[i+160+1];
    }
}

// Function to clear the screen by setting all characters to space and colors to black on white
void clear_screen() {
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f; // black background, white foreground
    }
}

// Function to print a string on the screen
void print(const char* str) {
    // Set cursor position to next line
    char* vidmem = (char*)0xb8000;
    int last_line = 0;
    for (int i = 0; i < 80 * 25 * 2; i += 160) {
        if (vidmem[i] != ' ') {
            last_line = i;
        }
    }

    int i = 0;
    last_line += 160;
    if (last_line >= 80 * 25 * 2) {
        unset_screen(); // If the last line is at the bottom, unset the screen by shifting content
    }
    
    // Print each character of the string
    while (str[i] != '\0') {
        vidmem[last_line + i * 2] = str[i];               // Set character
        vidmem[last_line + i * 2 + 1] = 0x0f;            // Set color attribute to white on blue
        i++;
    }
}
