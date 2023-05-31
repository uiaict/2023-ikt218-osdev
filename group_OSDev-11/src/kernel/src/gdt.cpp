#include "gdt.h"
#include <stdint.h>
#include "system.h"


struct gdt_entry gdt_descriptor[GDT_ENTRIES];
struct gdt_pointer gdt_pointer;

void gdt_descriptors(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_descriptor[num].base_low = (base & 0xFFFF); 
    gdt_descriptor[num].base_middle = (base >> 16) & 0xFF; 
    gdt_descriptor[num].base_high = (base >> 24) & 0xFF;

    gdt_descriptor[num].limit_low = (limit & 0xFFFF);
    gdt_descriptor[num].granularity = ((limit >> 16) & 0x0F);

    gdt_descriptor[num].granularity |= (gran & 0xF0);
    gdt_descriptor[num].access = access;
}

void initialize_gdt() asm ("initialize_gdt");

extern "C" {
    extern void flush_gdt(uint32_t);
}

void initialize_gdt()
{
    gdt_pointer.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gdt_pointer.base = (uint32_t)&gdt_descriptor;

    gdt_descriptors(0, 0, 0, 0, 0); // Null segment
    gdt_descriptors(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_descriptors(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_descriptors(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_descriptors(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    //flush old GDT implemented by GRUB and load new GDT
    flush_gdt((uint32_t)&gdt_pointer); 
}