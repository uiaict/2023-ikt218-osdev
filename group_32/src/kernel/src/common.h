// https://github.com/perara-lectures/ikt218-osdev/blob/master/group_per-arne/src/kernel/include/common.h

#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

// https://wiki.osdev.org/Serial_Ports
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

// ASCII table
const char asciiTable[] =
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};

#endif