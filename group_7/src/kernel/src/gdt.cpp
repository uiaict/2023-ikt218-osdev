/*
------------------------------------------------------------------------------
This file contains the implementation of the global description table.
------------------------------------------------------------------------------
*/

#include <stdint.h>
#include "gdt.h"

/// to be able to run the asm function from gdt.asm.
extern "C" {
  extern void gdt_flush(uint32_t gdt_ptr); 
}


void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // note: base & 0xFFFF ensures that only the lowest 16 bits of the base is left.
    gdt[num].base_low = (base & 0xFFFF);
    // note: base >> 16 is a bitshift that moves all bits 16 paces.
    // Then, base & 0xFF selects the first 8 bits. (bit 17-24 in base)
    gdt[num].base_middle = (base >> 16) & 0xFF;
    // note: Shifting base by 24, selects the last 8 bits of the base.
    gdt[num].base_high = (base >> 24) & 0xFF;

    // note: Like base, the limit is also split up into 16 bits.
    gdt[num].limit_low = (limit & 0xFFFF);

    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= gran & 0xF0;

    gdt[num].access = access;
}


void init_gdt()
{
    // Set the GDT limit and base.
    gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    // num, base, limit, access, granularity
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

  /// Load the GDT
  gdt_flush((uint32_t)&gdt_ptr);

}


