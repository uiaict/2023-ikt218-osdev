#include "gdt.h"
#include <stdint.h>
#include "system.h"

struct gdt_entry gdt_entries[GDT_ENTRIES];
struct gdt_ptr ptr_to_gdt;

extern "C" {
    extern void gdt_flush(uint32_t);
}

void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);
    
    gdt_entries[num].granularity |= granularity & 0xF0;
    gdt_entries[num].access      = access;
}

void gdt_init() asm ("gdt_init");

void gdt_init()
{
    ptr_to_gdt.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    ptr_to_gdt.base  = (uint32_t)&gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0);                     // Null segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);      // Code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);      // Data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);      // User mode code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);      // User mode data segment

    // Flush old GDT implemented by GRUB and load new GDT
    gdt_flush((uint32_t)&ptr_to_gdt); 
}
