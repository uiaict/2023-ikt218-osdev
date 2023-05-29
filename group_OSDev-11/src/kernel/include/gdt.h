#ifndef GDT_H
#define GDT_H

#include "system.h"
#include <stdint.h>

#define GDT_ENTRIES 5

struct gdt_entry 
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Global Descriptor Table pointer
struct gdt_ptr 
{
    uint16_t limit; 
    uint32_t base; 
} __attribute__((packed));

void gdt_init();

void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif /* GDT_H */
