#include "gdt.h"
struct gdt_entry_t gdt[GDT_ENTRIES];
struct gdt_ptr_t gdt_ptr;

extern "C"{
  extern void gdt_load(uint32_t);
}

void init_gdt() {
  // Set the GDT limit
  gdt_ptr.limit = sizeof(gdt) * GDT_ENTRIES - 1;
  gdt_ptr.base = (uint32_t) &gdt;
	
	// num, base, limit, access, granularity 
	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

  gdt_load((uint32_t)&gdt_ptr);
}

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].low_base    = (base & 0xFFFF);
    gdt[num].mid_base = (base >> 16) & 0xFF;
    gdt[num].high_base   = (base >> 24) & 0xFF;

    gdt[num].low_limit   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity = gran & 0xF0;
    gdt[num].access      = access;
}