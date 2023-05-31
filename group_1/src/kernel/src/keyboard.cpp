extern "C"
{
#include "system.h"
#include "../include/common.h"
#include "keyboard.h"
}

#define KEYBOARD_BUFFER_SIZE 256

// Scancodes for special keys
#define SCANCODE_CAPS_LOCK 0x3A
#define SCANCODE_LEFT_SHIFT 0x2A
#define SCANCODE_RIGHT_SHIFT 0x36
#define SCANCODE_LEFT_SHIFT_RELEASE 0xAA
#define SCANCODE_RIGHT_SHIFT_RELEASE 0xB6
#define SCANCODE_BACKSPACE 0x0E

// Keyboard state
static int caps_lock = 0;
static int left_shift = 0;
static int right_shift = 0;

// Keyboard buffer
static uint8_t keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static int buffer_start = 0;
static int buffer_end = 0;

// Add a scancode to the buffer
void add_scancode_to_buffer(uint8_t scancode) {
    keyboard_buffer[buffer_end] = scancode;
    buffer_end = (buffer_end + 1) % KEYBOARD_BUFFER_SIZE;
}

// Remove a scancode from the buffer
uint8_t get_scancode_from_buffer() {
    uint8_t scancode = keyboard_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % KEYBOARD_BUFFER_SIZE;
    return scancode;
}

// Check if the buffer is empty
int is_buffer_empty() {
    return buffer_start == buffer_end;
}

// Translate scancode to ASCII
char scancode_to_ascii(uint8_t scancode) {
    if (scancode < sizeof(ascii_lookup_table)) {
        return ascii_lookup_table[scancode];
    } else {
        return 0;
    }
}


// Keyboard handler function
extern "C" void keyboard_handler() {
    uint8_t scancode;
    char ascii_char;

    // Read the scancode from the keyboard data port (0x60)
    scancode = inb(0x60);

    // Check for special keys
    switch (scancode) {
        case SCANCODE_CAPS_LOCK:
            caps_lock = !caps_lock;
            return;
        case SCANCODE_LEFT_SHIFT:
            left_shift = 1;
            return;
        case SCANCODE_RIGHT_SHIFT:
            right_shift = 1;
            return;
        case SCANCODE_LEFT_SHIFT_RELEASE:
            left_shift = 0;
            return;
        case SCANCODE_RIGHT_SHIFT_RELEASE:
            right_shift = 0;
            return;
        case SCANCODE_BACKSPACE:
            printk("%c", SCANCODE_BACKSPACE);
            return;
        case 0x1C: // Enter key
            printk("\n");
            return;
        default:
            break;
    }

    // Translate scancode to ASCII
    ascii_char = scancode_to_ascii(scancode);

    // Handle Caps Lock and Shift
    if (ascii_char >= 'a' && ascii_char <= 'z') {
        if ((caps_lock && !left_shift && !right_shift) || (!caps_lock && (left_shift || right_shift))) {
            ascii_char -= 'a' - 'A';
        }
    } else if (ascii_char >= 'A' && ascii_char <= 'Z') {
        if ((caps_lock && !left_shift && !right_shift) || (!caps_lock && (left_shift || right_shift))) {
            ascii_char += 'a' - 'A';
        }
    }

    // If the scancode corresponds to a valid ASCII character, add it to the buffer
    if (ascii_char != 0) {
        printk("%c", ascii_char);
    }
}
