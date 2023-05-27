#include "../include/common.h"

// outb, inb and inw functions to directly access the hardware

// Write a byte out to the specified port.
void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value)); // asm volatile: insert assembly code directly to c code
}

uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inw(uint16_t port)
{
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

void *memset(void *ptr, int value, uint32_t num) {
    unsigned char *buffer = (unsigned char *)ptr;
    for (uint32_t i = 0; i < num; i++) {
        buffer[i] = (unsigned char)value;
    }
    return ptr;
}