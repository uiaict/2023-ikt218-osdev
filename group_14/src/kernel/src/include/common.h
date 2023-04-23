#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

// Source: https://wiki.osdev.org/Serial_Ports Fetched 17.04.23

void outb(uint16_t port, uint8_t value); // Byte-width port output
uint8_t inb(uint16_t port); // Byte-width port input
uint16_t inw(uint16_t port); // Word-width port input

#endif // COMMON_H