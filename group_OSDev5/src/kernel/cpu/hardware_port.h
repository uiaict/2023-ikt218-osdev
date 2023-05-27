
#ifndef UIAOS_HARDWARE_PORT_H
#define UIAOS_HARDWARE_PORT_H
#include "stdint.h"

// Write a byte out to the specified port.
void outb(uint16_t port, uint8_t value);

// Read a byte from the specified port.
uint8_t inb(uint16_t port);

// Read a word from the specified port.
uint16_t inw(uint16_t port);



#endif //UIAOS_HARDWARE_PORT_H