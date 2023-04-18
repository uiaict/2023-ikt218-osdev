#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_write(const char* data, size_t size);

#endif