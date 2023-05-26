#ifndef PRINTING_H
#define PRINTING_H

#include "common.h"
#include "cstdint"
#include "cstddef"

static inline uint16_t vga_entry(unsigned char uc, uint8_t color);

void clear_terminal(void);

void print(char word[80]);

void print_char (char c);

void print_logo();

#endif