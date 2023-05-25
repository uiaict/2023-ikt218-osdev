#include "gdt.h"

extern "C" void gdt_flush(uint32_t);

void init_gdt() asm ("init_gdt");

void gdt_set_entry(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

gdt_entry gdt[3];
gdt_ptr gp;

// Set the values of a GDT entry
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    //gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].base_high = static_cast<uint8_t>((base >> 24)) & static_cast<uint8_t>(0xFF);

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

// Initialize the GDT
void init_gdt()
{
    gp.limit = (sizeof(gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment

    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment, 0x08 offset from GDT base

    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment, 0x10 offset from GDT base

    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment

    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gp); // Load the GDT
}
