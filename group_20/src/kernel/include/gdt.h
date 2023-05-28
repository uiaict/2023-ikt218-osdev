#ifndef GDT
#define GDT
#include <stdint.h>

#define GDT_ENTRIES 5
#define IDT_ENTRIES 256

// Define the GDT entry structure
struct gdt_entry_t {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// Define the GDT pointers
struct gdt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

//Starts GDT
void start_gdt();

// Load the GDT
void gdt_load();

// Set the value of one GDT entry.
void set_gdt_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

static gdt_entry_t gdt[GDT_ENTRIES];
static gdt_ptr_t gdt_ptr;

#endif

// SOURCES: https://github.com/uiaict/ikt218-osdev/pull/1