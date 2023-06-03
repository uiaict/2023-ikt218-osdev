#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h> // for va_list

// Reverses a string of given length
void reverse(char* str, int length);

// Converts an integer to a string based on the given base
void itoa(int value, char *str, int base);

// Prints an integer to the monitor
void print_int(int num);

// Prints a string to the monitor
void print_str(char* str);

// Prints a character to the monitor
void print_char(char c);

// Prints formatted output to the monitor
void printf(char *str, ...);

#endif