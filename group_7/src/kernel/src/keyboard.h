#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

/// @brief Function to register the keyboard interrupt handler.
void keyboard_handler();

/// @brief Function to convert a scancode to an ascii character.
/// @param scancode The scancode to convert.
/// @return ascii character
char convert_to_ascii(uint8_t scancode);

#endif