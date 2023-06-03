#include "system.h"

#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Defines the total number of entries in the GDT
#define GDT_ENTRIES 5

// GDT entry structure
// Each GDT entry defines a segment in memory
struct gdt_entry 
{
    uint16_t limit_low;    // Lower 16 bits of the limit
    uint16_t base_low;     // Lower 16 bits of the base address
    uint8_t base_middle;   // Next 8 bits of the base address
    uint8_t access;        // Access flags define what ring this segment can be used in
    uint8_t granularity;   // Granularity flag
    uint8_t base_high;     // Last 8 bits of the base address
} __attribute__((packed)); // This attribute ensures gcc won't try to optimize the storage for this struct

// This structure describes a pointer to the GDT and its limit
struct gdt_pointer 
{
    uint16_t limit; // Size of the GDT table - 1
    uint32_t base;  // Address to the first entry in GDT
} __attribute__((packed)); // Same reason as above for the attribute

// Declare functions to initialize GDT and to set a GDT entry
// They are actually implemented in the corresponding .cpp file

// This function initializes the GDT
void initialize_gdt();

// This function sets an entry in the GDT
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif /* GDT_H */
