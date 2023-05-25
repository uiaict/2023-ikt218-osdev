#ifndef GDT_H
#define GDT_H

#include <stdint.h>

// Structure representing a GDT entry
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Structure representing the GDT pointer
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Function declarations
extern "C" void gdt_flush(uint32_t);
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void init_gdt();

#endif
