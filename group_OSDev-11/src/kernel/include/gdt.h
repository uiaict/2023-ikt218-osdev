#include "system.h"
#ifndef GDT_H
#define GDT_H
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
} __attribute__((packed)); // For gcc to use as little memory as possible

// Local descriptor table pointer
struct gdt_pointer 
{
    uint16_t limit; // 16 bit limit. Size of the GDT
    uint32_t base; // 32 bit pointer. First entry in GDT
} __attribute__((packed));


void initialize_gdt();

void gdt_descriptors(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif /* GDT_H */