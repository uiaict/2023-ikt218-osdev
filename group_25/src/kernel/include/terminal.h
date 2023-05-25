#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
// Initializes the terminal
void terminal_initialize(void);
// Writes text to the terminal
void terminal_write(const char* data, size_t size);

#endif 