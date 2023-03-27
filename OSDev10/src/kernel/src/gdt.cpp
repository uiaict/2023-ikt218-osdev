#include "gdt.h"

extern "C" {
  extern void gdt_flush(uint32_t gdt_ptr);
}

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdt_ptr;

void init_gdt() {
  // Set the GDT limit
  gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
  gdt_ptr.base = (uint32_t) &gdt;
	
  gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	// Flush GDT pointer
	gdt_flush((uint32_t)&gdt_ptr);
}



void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access      = access;
}
