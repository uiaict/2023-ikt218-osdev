// Written by the IKT218 Group 39 in the spring 2023.

#include "gdt.h" // Include our GDT header file.

// Extern "C" allows us to call code that has been implemented in assembly. 
extern "C"
{
    extern void gdt_load(uint32_t); // Refers to a function in assembly that loads the GDT register.
}


void init_gdt() asm ("init_gdt"); // Lets init_gdt be called from assembly.

void gdt_set_entry (int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity); // Declare this function beforehand

// Create an array of 3 GDT entries (NULL, Data and Text) 
// as well as a GDT pointer on stack.

gdt_entry gdt_entries[3];
gdt_pointer gdt_ptr;

void init_gdt()
{
    // Set up GDT pointer
    gdt_ptr.limit = (sizeof(gdt_entry) * 3) -1 ; // Set the limit to be the size of the number of entries in the GDT. 
    gdt_ptr.base  = (uint32_t)&gdt_entries;     //  This sets the base of the GDT pointer to be the starting address of the GDT table. 

    // Creating segment descriptors
    gdt_set_entry(0, 0, 0, 0, 0); // Null segment descriptor
    gdt_set_entry(1, 0, 0XFFFFFFFF, 0x9A, 0xCF); // Code segment descriptor 
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment descriptor

    // Finally, load the GDT. 
    gdt_load((uint32_t)&gdt_ptr); // This calls the gdt_load function, 
                                  // and passes the address of the gdt pointer to that assembly function.
}

// gdt_set_entry is a function based on the lecturer's implementation of 'gdt_set_gate'
// This function takes the following arguments:
// Num: The index of the GDT entry
// Base: The 32-bit base address for the segment
// Limit: The 32-bit limit for the segment
// Access: The access flags for the segment
// Granularity: The granularity of the segment.
void gdt_set_entry (int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
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
