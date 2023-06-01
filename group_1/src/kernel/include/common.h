// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void *memset(void *ptr, int value, uint32_t num);

#endif