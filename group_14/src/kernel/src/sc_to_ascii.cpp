// Scancode to ASCII source: http://www.osfree.org/docs/cmdref/cmdref.2.0476.php

#include "./include/sc_to_ascii.h"

unsigned char scancode_table[TABLE_SIZE] = {
    // Main keyboard
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, // Esc, 1, 2, 3 ,4 ,5 ,6 ,7, 8, 9, 0, -, =, Backspace
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, // Tab, q, w, e, r, t, y, u, i, o, p, [, ], Enter
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 43, 44, 
    45, 46, 47, 48, 49, 50, 51, 52, 53, 57,// 1, 2, 3 ,4 ,5 ,6 ,7 ,8, 9, 0, -, =, Backspace
    59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 133, 134, // F1

    // Numpad and Control Pad keys
    55, 71, 71, 72, 72, 73, 73, 74, 75, 75, 76, 77, 77, 78, 79, 79, 80, 80, 
    81, 81, 82, 82, 83, 83, 224, 224, 55, 0, 0, 0, 0, 0, 42, 0, 224, 0, 224, 
    0, 0, 0, 224, 0, 224, 0, 224, 0, 45, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    224, 0, 224, 0, 224, 0, 0, 0, 224, 0, 224, 0, 224, 0, 43, 0, 13
};

unsigned char ascii_table[TABLE_SIZE] = {
    // Main keyboard
    27, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 45, 61, 8, 9, // Esc, 1, 2, 3 ,4 ,5 ,6 ,7, 8, 9, 0, -, =, Backspace
    113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 91, 93, 13, // Tab, q, w, e, r, t, y, u, i, o, p, [, ], Enter
    97, 115, 100, 102, 103, 104, 106, 107, 108, 59, 39, 96, 92,
    122, 120, 99, 118, 98, 110, 109, 44, 46, 47, 32, 

    // Numpad and Control pad keys
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 0, 224, 0, 224, 0, 224, 0, 
    45, 0, 0, 0, 43, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 0, 224, 
    0, 224, 0, 0, 0, 224, 0, 224, 0, 224, 0, 43, 0, 13
};

// Convert scancode to ascii
char scancode_to_ascii(unsigned char scancode) {
    for (int i = 0; i <= TABLE_SIZE; i++) {
        if (scancode == scancode_table[i]) {
            asm volatile("cli");
            return ascii_table[i];
        }
    }
    asm volatile("cli");
    return '\0';
}