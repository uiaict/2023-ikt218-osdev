#ifndef gdt_h
#define gdt_h

#include <stdint.h>

// Define a struct to represent the GDT entry
struct GDT {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;
};

// Declare the function prototype for the encodeGdtEntry function
void encodeGdtEntry(uint8_t *target, struct GDT source);

#endif 