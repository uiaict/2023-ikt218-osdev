#include "system.h"

// If the header file GDT_HEADER is not defined, define it
#if !defined(GDT_HEADER)
#define GDT_HEADER

#include <stdint.h>

// Define the number of entries in the GDT
#define GDT_ENTRY_COUNT 5

// Define the structure of a GDT entry
typedef struct 
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t; // For gcc to use as little memory as possible

// Define the local descriptor table pointer
typedef struct {
    uint16_t limit; // 16 bit limit. Size of the GDT
    uint32_t base; // 32 bit pointer. First entry in GDT
} __attribute__((packed)) gdt_ptr_t;

// Initialize the GDT
void init_gdt();

// Set a GDT entry
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// Function in lgdt.asm to reload new segment registers
extern void flush_gdt();

#endif /* GDT_HEADER */