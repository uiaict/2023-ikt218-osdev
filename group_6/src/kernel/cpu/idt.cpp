#include "idt.h"
#include <memory.h>
#include "hardware_port.h"


void init_idt() asm ("init_idt");
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

extern "C"{
    void idt_flush(uint32_t);

    // Lets us use assembly functions in C
    extern void isr0 ();
    extern void isr1 ();
    extern void isr2 ();
    extern void isr3 ();
}


// Array of all entries
idt_entry_t idt_entries[NUM_IDT_ENTRIES];   
// Pointer that lets us know beginning and endpoint of the array of entries
idt_ptr_t   idt_ptr;                        

void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * NUM_IDT_ENTRIES -1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // memset(&idt_entries, 0, sizeof(idt_entry_t)*NUM_IDT_ENTRIES);

    // Remap the irq table.
    
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    idt_set_gate( 0, (uint32_t)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uint32_t)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uint32_t)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (uint32_t)isr3 , 0x08, 0x8E);
    


    idt_flush((uint32_t)&idt_ptr);
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags  | 0x60;
}