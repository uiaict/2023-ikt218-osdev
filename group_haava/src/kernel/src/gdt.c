#include "gdt.h"


struct gdt_entry gdt_ptr[GDT_ENTRIES];

/* Called from assembly, loads GDT and update segments. */
extern void gdt_load(struct gdt_ptr *gdt);

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit,
                         uint8_t access, uint8_t granularity)
{
    gdt_ptr[num].base_low = (base & 0xFFFF);
    gdt_ptr[num].base_middle = (base >> 16) & 0xFF;
    gdt_ptr[num].base_high = (uint8_t) (base >> 24) & 0xFF;

    gdt_ptr[num].limit_low = (limit & 0xFFFF);
    gdt_ptr[num].granularity = (limit >> 16) & 0x0F;

    gdt_ptr[num].granularity |= granularity & 0xF0;
    gdt_ptr[num].access = access;
}

void gdt_init()
{
    struct gdt_ptr gdt;
    gdt.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
    gdt.base = (uint32_t) &gdt_ptr;

    gdt_set_gate(0, 0, 0, 0, 0);                /* Null segment */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */

    gdt_load(&gdt);
}
