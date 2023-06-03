/*
    code sourced from 
    http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
    https://github.com/cfenollosa/os-tutorial/blob/master/18-interrupts/cpu/idt.h
    https://github.com/perara/ikt218-advanced-operating-systems/blob/master/src/kernel/cpu/i386/idt.h
*/

// prevent duplicate definitions
#ifndef INTERRUPT_DESCRIPTOR_TABLE
#define INTERRUPT_DESCRIPTOR_TABLE

#define IDT_ENTRIES 256


#include <stdint.h>


// A struct describing an interrupt gate.
struct idt_entry_struct
{
   uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));


// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));



typedef struct idt_entry_struct idt_entry_t;
typedef struct idt_ptr_struct idt_ptr_t;

void init_idt();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
#endif