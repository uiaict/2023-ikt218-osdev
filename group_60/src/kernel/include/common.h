#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

// https://wiki.osdev.org/Serial_Ports
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

#endif
