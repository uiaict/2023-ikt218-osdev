#ifndef TERMINAL_H
#define TERMINAL_H
#include <stdint.h>
#include "system.h"

void initialize_terminal();
void write_to_terminal(const char* str);
void terminal_write_char(char c);

#endif