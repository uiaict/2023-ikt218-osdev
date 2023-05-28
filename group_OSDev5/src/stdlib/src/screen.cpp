#include "screen.h"

void unset_screen(){
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = vidmem[i+160];
        vidmem[i+1] = vidmem[i+160+1];
    }
}

void clear_screen() {
    char* vidmem = (char*)0xb8000;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vidmem[i] = ' ';
        vidmem[i+1] = 0x0f; // black background, white foreground
    }
}



void print_int(int32_t num) {
    char num_str[12]; // Buffer to hold the number as a string, up to 11 digits plus null terminator
    int i = 0;

    // Handle zero explicitly to simplify the rest of the code
    if (num == 0) {
        print("0");
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        print("-");
        num = -num; // Make the number positive so the rest of the code works
    }

    // Convert each digit to a character, starting from the end
    while (num > 0) {
        num_str[i] = '0' + num % 10; // Convert the digit to a character
        num /= 10; // Remove the last digit
        i++;
    }

    // The digits are in reverse order, so print them from end to start
    for (int j = i - 1; j >= 0; j--) {
        char digit_str[2] = { num_str[j], '\0' }; // Convert the digit character to a string
        print(digit_str);
    }
}


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
    if(last_line >= 80 * 25 * 2){
        unset_screen();
    }
    while (str[i] != '\0') {
        vidmem[last_line + i * 2] = str[i];
        vidmem[last_line + i * 2 + 1] = 0x0f; // Set color attribute to white on blue
        i++;
    }
}