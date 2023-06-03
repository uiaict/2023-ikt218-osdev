#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"

// Some defines for readability
#define KB_BUFFER_SIZE 256
#define KB_PORT 0x60
#define SCANCODE_CAPS_LOCK 0x3A
#define SCANCODE_L_SHIFT 0x2A
#define SCANCODE_R_SHIFT 0x36
#define SCANCODE_ENTER 0x1C
#define SCANCODE_BACKSPACE 0x0E
#define SCANCODE_TAB 0x0F
#define SCANCODE_R_ALT 0x38
#define RELEASE 0x80


void keyboard_processing(registers_t regs);

char keyboard_read();

char to_uppercase(char c);

#endif