#include <cstdint>
#include "gdt.h"

extern "C" void gdt_flush(uint32_t);

gdt_entry GDT::gdt_entries[3];
gdt_pointer GDT::gdt_ptr;

static void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    GDT::gdt_entries[num].base_low = base & 0xFFFF;
    GDT::gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    GDT::gdt_entries[num].base_high = (base >> 24) & 0xFF;

    GDT::gdt_entries[num].limit_low = limit & 0xFFFF;
    GDT::gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    GDT::gdt_entries[num].granularity |= granularity & 0xF0;
    GDT::gdt_entries[num].access = access;
}

void GDT::init() {
    gdt_ptr.limit = (sizeof(gdt_entry) * 3) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_entry(0, 0, 0, 0, 0);                // NULL descriptor
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment descriptor
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment descriptor

    gdt_flush((uint32_t)&gdt_ptr);
}