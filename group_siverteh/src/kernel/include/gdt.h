/* Not self written code, found code at http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html */
#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/* Defines the number of entries in the GDT. */
#define GDT_ENTRIES 5

/* 
Defines a struct called gdt_entry which represents one entry in the GDT. The various fields
Within the struct corresponds to the different components of a GDT entry.
*/
struct gdt_entry_t
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.          
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

//Defines another struct called gdt_ptr that contains the size and base address of the GDT.
struct gdt_ptr_t
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

/*FUNCTION DECLARATIONS*/
//Loads the GDT into the processors memory.
void load_gdt();

//Sets the value of one GDT entry.
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif