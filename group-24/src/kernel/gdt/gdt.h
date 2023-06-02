#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ENTRIES 3

// Structure representing a GDT entry
struct gdt_entry {
    uint16_t limit_low;    // The lower 16 bits of the limit
    uint16_t base_low;     // The lower 16 bits of the base address
    uint8_t base_middle;   // The next 8 bits of the base address
    uint8_t access;        // Access flags
    uint8_t granularity;   // Granularity and size flags
    uint8_t base_high;     // The last 8 bits of the base address
} __attribute__((packed));

// Structure representing the GDT pointer
struct gdt_ptr {
    uint16_t limit;        // The upper 16 bits of all selector limits
    uint32_t base;         // The address of the first gdt_entry struct
} __attribute__((packed));

void init_gdt();    // Function to initialize the GDT
//void gdt_flush();   // Function to load the GDT


void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

[[maybe_unused]] static gdt_entry gdt[GDT_ENTRIES];
[[maybe_unused]] static gdt_ptr gp;

#endif
