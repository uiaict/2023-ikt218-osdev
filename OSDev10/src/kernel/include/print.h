// print.h -- Defines the interface for monitor.h
// Based on JamesM's kernel development tutorials.

#ifndef PRINT_H
#define PRINT_H

#include "common.h"

// Write a char to the screen.
void print_char(char c);

// Clear the screen.
void clear_screen();

// write a string tot eh screen and end with a newline
void print_string(char *c);

#endif // PRINT_H