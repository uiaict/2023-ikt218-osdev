// Protection against multiple inclusions. 
#ifndef GDT_H
#define GDT_H

// Includes the system header file
#include "system.h"
// Includes the standard integer types
#include <stdint.h>

// Defines the number of entries in the Global Descriptor Table
#define GDT_ENTRIES 5

// Defines the structure of a GDT entry
struct gdt_entry 
{
    uint16_t limit_low;     // Defines the lower 16 bits of the limit
    uint16_t base_low;      // Lower 16 bits of the base
    uint8_t base_middle;    // Next 8 bits of the base
    uint8_t access;         // Access flags determine what ring this segment can be used in
    uint8_t granularity;    // Specifies granularity and other features of the segment
    uint8_t base_high;      // The last 8 bits of the base
} __attribute__((packed));  // Ensures the struct is packed and no extra bytes are added by the compiler

// Defines the structure of a GDT pointer. It points to the start of the GDT and also includes the size of the GDT.
struct gdt_ptr 
{
    uint16_t limit;         // Size of the GDT
    uint32_t base;          // The address of the first gdt_entry_t structure
} __attribute__((packed));  // Ensures the struct is packed and no extra bytes are added by the compiler

// Declares the function to initialize the GDT
void gdt_init();

// Declares the function to set a value in a GDT entry
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif /* GDT_H */