// Not self written code, found code at http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
#ifndef IDT_H
#define IDT_H

#include <cstdint>

//Defines the number of entries in the IDT.
#define IDT_ENTRIES 256


/* 
Defines a struct called idt_entry which represents one entry in the IDT. The various fields
Within the struct corresponds to the different components of a IDT entry.
*/
struct idt_entry_t
{
   uint16_t base_low;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_high;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

//Defines another struct called idt_ptr that contains the size and base address of the IDT.
struct idt_ptr_t
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

/*FUNCTION DECLARATIONS*/
//Sets the value of one IDT entry.
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

//Loads the IDT into the processors memory
void load_idt();

#endif