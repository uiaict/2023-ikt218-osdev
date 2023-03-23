# include "gdt.h"

void gdt_init() asm ("gdt_init");

extern "C" {
    extern void gdt_flush(uint32_t);
    static void gdt_setGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
}

UIAOS::CPU::GDT::gdt_entry gdt_entries[6];
UIAOS::CPU::GDT::gdt_ptr gdt_ptr;

void gdt_init() {
    gdt_ptr.limit = (sizeof(UIAOS::CPU::GDT::gdt_entry)*6) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_setGate(0, 0, 0, 0, 0);                // Null segment
    gdt_setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gdt_ptr);  
}



void gdt_setGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = access;
}