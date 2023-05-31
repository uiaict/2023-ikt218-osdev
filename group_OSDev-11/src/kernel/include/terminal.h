#ifndef DISPLAY_TERMINAL_H
#define DISPLAY_TERMINAL_H

#include <stdint.h>
#include "system.h"

// Initializes the terminal
void initialize_terminal();

// Outputs a string to the terminal
void output_to_terminal(const char* data);

// Outputs a single character to the terminal
void output_character_to_terminal(char character);

#endif /* DISPLAY_TERMINAL_H */
