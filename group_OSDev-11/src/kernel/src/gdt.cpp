#include "gdt.h"
#include <stdint.h>
#include "system.h"

// Declare GDT entries and pointer
struct gdt_entry gdt_descriptor[GDT_ENTRIES];
struct gdt_pointer gdt_pointer;

// This function fills a GDT entry
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // Set the base address
    gdt_descriptor[num].base_low = (base & 0xFFFF); 
    gdt_descriptor[num].base_middle = (base >> 16) & 0xFF; 
    gdt_descriptor[num].base_high = (base >> 24) & 0xFF;

    // Set the limit
    gdt_descriptor[num].limit_low = (limit & 0xFFFF);
    gdt_descriptor[num].granularity = ((limit >> 16) & 0x0F);

    // Set the granularity and access flags
    gdt_descriptor[num].granularity |= (gran & 0xF0);
    gdt_descriptor[num].access = access;
}

// External asm function to initialize GDT
void initialize_gdt() asm ("initialize_gdt");

extern "C" {
    // External asm function to flush the old GDT and load the new one
    extern void flush_gdt(uint32_t);
}

// This function initializes the GDT
void initialize_gdt()
{
    // Set GDT pointer
    gdt_pointer.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gdt_pointer.base = (uint32_t)&gdt_descriptor;

    // Null segment
    set_gdt_entry(0, 0, 0, 0, 0);
    // Code segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Data segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // User mode code segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // User mode data segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // Flush old GDT and load the new GDT
    flush_gdt((uint32_t)&gdt_pointer);
}
