#include "common.h"

void write_to_port(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t read_byte_from_port(uint16_t port)
{
   uint8_t result;
   asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));
   return result;
}

uint16_t read_word_from_port(uint16_t port)
{
   uint16_t result;
   asm volatile ("inw %1, %0" : "=a" (result) : "dN" (port));
   return result;
}