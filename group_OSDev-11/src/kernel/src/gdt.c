#include "gdt.h"
#include <stdint.h>
#include "system.h"

// Declare an array of GDT entries
gdt_entry_t gdt_entries[GDT_ENTRY_COUNT];

// Declare a GDT pointer struct
gdt_ptr_t gdt_pointer;

// Set a GDT entry with the given parameters
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    gdt_entries[num].granularity |= (gran & 0xF0);
    gdt_entries[num].access = access;
}

// Initialize the Global Descriptor Table (GDT)
void init_gdt()
{
    // Set the GDT pointer to the location of the GDT entries
    gdt_pointer.limit = (sizeof(gdt_entry_t) * GDT_ENTRY_COUNT) - 1;
    gdt_pointer.base = (uint32_t)&gdt_entries;

    // Set up GDT entries for null segment, code segment, data segment, and user mode segments
    set_gdt_entry(0, 0, 0, 0, 0); // Null segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    // Flush the old GDT implemented by GRUB and load the new GDT
    flush_gdt();
}