#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H
#include <stdint.h>

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define GDT_ENTRIES 5

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

void init_gdt();

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);


/* Our GDT, with 3 entries, and finally our special GDT pointer */
static gdt_entry gdt[GDT_ENTRIES];
static gdt_ptr gp;