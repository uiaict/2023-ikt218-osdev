#include "common.h"

// Function to write a byte to a specified port
void write_to_port(uint16_t port, uint8_t value)
{
    // "outb %1, %0" is an assembly instruction that writes the value in register %1 (here "a" or 'value') 
    // to the I/O port specified in register %0 (here "dN" or 'port')
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// Function to read a byte from a specified port
uint8_t read_byte_from_port(uint16_t port)
{
   uint8_t ret;
   // "inb %1, %0" is an assembly instruction that reads a byte from the I/O port specified in register %1 
   // (here "dN" or 'port') and stores it in register %0 (here "a" or 'ret')
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret; // Returns the byte read from the port
}

// Function to read a word (2 bytes) from a specified port
uint16_t read_word_from_port(uint16_t port)
{
   uint16_t ret;
   // "inw %1, %0" is an assembly instruction that reads a word from the I/O port specified in register %1 
   // (here "dN" or 'port') and stores it in register %0 (here "a" or 'ret')
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret; // Returns the word read from the port
}