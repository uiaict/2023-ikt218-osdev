#include "gdt.h"

gdt_entry_t gdt_entries[GDT_SIZE];
gdt_ptr_t gdt_ptr;

// Allow the init_gdt function to be called from assembly
void init_gdt() asm ("init_gdt");

// Allow the assembly function gdt_flush to be called from c++
extern "C" {
    extern void gdt_flush(uint32_t);
}

// Set GDT entries
void gdt_set_gate(int32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt_entries[i].base_low = (base & 0xFFFF);
    gdt_entries[i].base_middle = (base >> 16) & 0xFF;
    gdt_entries[i].base_high = (base >> 24) & 0xFF;
    gdt_entries[i].limit_low = (limit & 0xFFFF);
    gdt_entries[i].granularity = (limit >> 16) & 0x0F;
    gdt_entries[i].granularity |= gran & 0xF0;
    gdt_entries[i].access = access;
}

// Initialize the global descriptor table
void init_gdt(){
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_SIZE - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0,          0,    0,    0); // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gdt_ptr);
}