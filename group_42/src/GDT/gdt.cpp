// copied from privied github repository

#include "gdt.h"
#define GDT_ENTRIES 5 // sets the number of segments

IJI_OS::GDT::gdt_entry_t gdt[GDT_ENTRIES];
IJI_OS::GDT::gdt_ptr_t gdt_ptr;


void IJI_OS::GDT::init_gdt() asm ("init_gdt"); // This line gives assambly acess to the function init_gdt


extern "C" {
    extern void gdt_flush(uint32_t); // this line gives the file access to the assably function gdt_flush

    
}


void IJI_OS::GDT::init_gdt()
{
    
    gdt_ptr.limit = sizeof( IJI_OS::GDT::gdt_entry_t) * GDT_ENTRIES - 1; // setts the limit size of the GDT
    gdt_ptr.base = (uint32_t)&gdt;  // sets the up the base or memory address of the GDT

    // here we use the gdt_set_gate to sett opp the segmets in the Global Deskriptor Table.
    gdt_set_gate(0, 0, 0, 0, 0);     // the zero segment    
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // the code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // the data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // the user code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // the user data segment

   
    
    gdt_flush((uint32_t)&gdt_ptr); // the GDT_flush function loads the gdt on to memmory
}


void IJI_OS::GDT::gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF); // memmory address
    gdt[num].base_middle = (base >> 16) & 0xFF; // memmory address
    gdt[num].base_high = (base >> 24) & 0xFF; // memmory address

    gdt[num].limit_low = (limit & 0xFFFF); // sets the size of the segment with granuarity
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0; // setts the scale of the segment
    gdt[num].access = access;    // decies how the segment can be accesed 
}