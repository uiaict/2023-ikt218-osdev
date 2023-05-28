//Code found here: http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
#include "gdt.h"

//The external function gdt_flush() is declared.
extern "C"
{
    void gdt_flush(uint32_t gdt_ptr);
}

//Sets up instances of the structs gdt_entry and gdt_ptr.
static gdt_entry_t gdt_entries[GDT_ENTRIES];
static gdt_ptr_t   gdt_ptr;

//Set the value of one GDT entry.
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    //The first three lines sets the base address of the segment.
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    //The next two lines sets the limit of the segment.
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    //The last line sets the access flags for the segment.
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

//load_gdt() sets up the GDT by creating GDT entries for the null segment, code segment, data segment, and user mode code/data segments.
void init_gdt()
{
    //Sets the limit field to the size of gdt_entry multiplied by the amount of entries.
    gdt_ptr.limit = sizeof(struct gdt_entry_t) * GDT_ENTRIES - 1;
    //Sets the base field to the memory address of the gdt_entries, which is the address of the first element in the array.
    gdt_ptr.base = (uint32_t)&gdt_entries;

    //Sets the value of each segment in the GDT.
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    //Loads the GDT into the processors memory.
    gdt_flush((uint32_t)&gdt_ptr);
}
