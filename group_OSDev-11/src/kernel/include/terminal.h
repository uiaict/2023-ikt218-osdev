// This is a header guard. It prevents the header file from being included multiple times by the preprocessor.
#ifndef TERMINAL_H
#define TERMINAL_H

// This includes the standard integer types like int16_t, int32_t, etc.
#include <stdint.h>

// This includes "system.h", which probably contains system-level definitions and function prototypes that are used by the terminal.
#include "system.h"

// This is a function prototype for initializing the terminal. 
void initialize_terminal();

// This is a function prototype for writing a string to the terminal. The string to be written is passed as a const char pointer.
void write_to_terminal(const char* str);

// This is a function prototype for writing a single character to the terminal. The character to be written is passed as a char.
void output_char_to_terminal(char c);

// This ends the header guard. If TERMINAL_H was defined, the preprocessor will stop skipping lines here.
#endif
