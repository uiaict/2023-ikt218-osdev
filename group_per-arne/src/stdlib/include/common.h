#ifndef COMMON_H
#define COMMON_H
#include <stdint.h>

char* hex32_to_str(char buffer[], unsigned int val);
char* int32_to_str(char buffer[], int val);


void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

#endif

