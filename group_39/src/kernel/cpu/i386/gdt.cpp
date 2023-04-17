// Written by the IKT218 Group 39 in the spring 2023.

#include "gdt.h" // Include our GDT header file.




// Create an array of 3 GDT entries (NULL, Data and Text) 
// as well as a GDT pointer on stack.
gdt_entry gdt_entries[3];
gdt_pointer gdt_ptr;



gdt_entries[0] = {0,0,0,0,0,0}; // NULL descriptor
gdt_entries[1] = {0xFFFF, 0x0000, 0x00, 0x9A, 0xCF, 0x00}; // Code descriptor
gdt_entries[2] = {0xFFFF, 0x0000, 0x00, 0x92, 0xCF, 0x00}; // Data descriptor



// gdt_set_entry is a function based on the lecturer' implmentation of 'gdt_set_gate'
// This function takes the 
gdt_set_entry (int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    // Set the base address fields
    gdt_entries[num].base_low = (base & 0xFFFF);        // Set the lower 16 bits of the base address
    gdt_entries[num].base_middle = (base >> 16) & 0xFF; // Set the middle 8 bits of the base address
    gdt_entries[num].base_high = (base >> 24) & 0xFF;   // Set the upper 8 bits of the base address


    // Set the limit field
    gdt_entries[num].limit_low = (limit & 0xFFFF);

    // Set the granularity fields
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= granularity & 0xF0;

    // Set the access field
    gdt_entries[num].access = access;
}
