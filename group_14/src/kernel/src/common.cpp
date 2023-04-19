#include "../include/common.h"

void outb(uint16_t port, uint16_t value) {
    asm volatile ("out %1, %0" : : "dN" (port), "a" (value)); // Embeds assembly code and uses port and value as input parameters
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port)); // Embeds assembly code, sets ret and takes port as input parameter
    return ret;
}

uint16_t inw(uint16_t port){
   uint16_t ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port)); // Embeds assembly code, sets ret and takes port as input parameter
   return ret;
}