#include "./include/sc_to_ascii.h"

unsigned char scancode_table[TABLE_SIZE] = {
    /*0x76, 0x05, 0x06, 0x04, 0x0C, 0x03, 0x0B, 0x83, 0x0A, 0x01, 0x09, 0x78, 0x07, // ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
    0xE012E07C, 0x7E, 0xE11477E1F014E077, 0x0E // Prt Screen, Scroll lock, Pause/Break, `*/

    0x16, 0x1E, 0x26, 0x25, 0x2E, 0x36, 0x3D, 0x3E, 0x46, 0x45, 0x4E, 0x55, 0x66, // 1, 2, 3 ,4 ,5 ,6 ,7 ,8, 9, 0, -, =, Backspace
    0x0D, 0x15, 0x1D, 0x24, 0x2D, 0x2C, 0x35, 0x3C, 0x43, 0x44, 0x4D, 0x54, 0x5B, 0x5D, // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], \,
    /*0x58*/ 0x1C, 0x1B, 0x23, 0x34, 0x33, 0x3B, 0x42, 0x4B, 0x4C, 0x52, // Caps Lock, A, S, D, F, G, H, J, K, L, ;, '
    /*0x5A, 0x12*/ 0x1A, 0x22, 0x21, 0x2A, 0x32, 0x31, 0x3A, 0x41, 0x49, 0x4A // Enter, Shift(left), Z, X, C, V, B, N, M, ",", ".", "/"

    /*0x59, 0x14, 0xE01F, 0x11, 0x29, 0xE011, 0xE027, 0xE02F, 0xE014, 0xE070, // Shift(Right), Ctrl(left), Windows(left), Alt(left), Spacebar, Alt(right), Windows(right), Menus, Ctrl(right), Insert
    0xE06C, 0xE07D, 0xE071, 0xE069, 0xE07A, 0xE075, 0xE06B, 0xE072,  0xE074, // Home, Page Up, Delete, End, Page Down, Up Arrow, Left Arrow, Down Arrow, Right Arrow

    // Numpad
    0x77, 0xE04A, 0x7C, 0x7B, // Num Lock, /, *, -
    0x6C, 0x75, 0x7D, 0x79, // 7, 8, 9, +
    0x6B, 0x73, 0x74, // 4, 5, 6
    0x69, 0x72, 0x7A, // 1, 2, 3
    0x70, 0x71, 0xE05A // 0, ".", Enter*/
};

unsigned char ascii_table[TABLE_SIZE] = {
    49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 45, 61, 8, // 1, 2, 3 ,4 ,5 ,6 ,7 ,8, 9, 0, -, =, Backspace
    9, 81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 91, 93, 92, // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], \,
    65, 83, 68, 70, 71, 72, 74, 75, 76, 59, 39, // A, S, D, F, G, H, J, K, L, ;, '
    90, 88, 67, 86, 66, 77, 78, 44, 46, 47 // Z, X, C, V, B, N, M, ",", ".", "/"
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