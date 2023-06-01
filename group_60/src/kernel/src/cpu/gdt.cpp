#include <descriptor_tables.h>


// include gdt_flush from assembly file
extern "C" {
    extern void gdt_flush(uint32_t gp);
}


/** Set values of a GDT segment 
 * num - which gdt segment (0-4), 
 * limit - space limit
 * access - what access level it should be set to,
 * gran - amount of gran space
*/
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}


// Does all the necessery things to start up the GDT
void init_gdt()
{
    /* Setup the GDT pointer and limit */
    gp.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
    gp.base = (uint32_t) &gdt;

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);
    /* Our Code Segment with 4GBytes limit and 4Kbyte gran*/
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    /* Our Data Segment, same as code segment just different access level*/
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    /* Our User Code Segment, same again just different access level*/
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    /* Our User Data Segment, same again just different access level*/
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // Load GDT
    gdt_flush((uint32_t)&gp);
}




