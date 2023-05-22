#include "gdt.h"

extern "C" void gdt_flush(uint32_t);

// Define the GDT entries
gdt_entry gdt[3];
gdt_ptr gp;

// Function to set up a GDT entry
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low    = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;
    gdt[num].limit_low   = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}

// Function to initialize the GDT
void init_gdt() {
    gp.limit = sizeof(gdt) - 1;
    gp.base  = (uint32_t)&gdt;

    // Set up the GDT entries
    gdt_set_gate(0, 0, 0, 0, 0);                      // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);       // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);       // Data segment

    // Flush the GDT pointer
    gdt_flush((uint32_t)&gp);
}
