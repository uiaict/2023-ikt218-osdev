// Written by Group 39 IKT218 Project Spring 2023

#include "idt.h"
#include "../../memory/memory.h"
#include "interrupts.h"
#include "../../common/common.h"



extern "C"
{
    extern void idt_load(uint32_t); // Refers to a function in assembly that loads the IDT register.
}



void init_idt() asm ("init_idt"); // This allows assembly code to call our 'init_gdt' function.




void idt_set_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_low = base & 0xFFFF; // Set the lower 16 bits of the base address. 
    idt_entries[num].base_high = (base >> 16) & 0xFFFF; // Set the upper 16 bits of the base address.

    idt_entries[num].selector = sel; // Set segment selector
    idt_entries[num].reserved = 0; // Set the "Reserved/always0" field to 0. 
    idt_entries[num].flags    = flags | 0x60; // Set flags.
}



// This function sets up and loads the IDT. 
void init_idt()
{
    idt_pointer.base = (uint32_t)&idt_entries; // Set the base address of the IDT pointer.
    idt_pointer.limit = sizeof(idt_entry) * NUM_IDT_ENTRIES -1; // Set the limit of the IDT pointer. 

    // Zero out all IDT entries, just in case they contain any garbage. Should be zero because it is a global variable without any initialiser. 
    memset(&idt_entries, 0, sizeof(idt_entry)*NUM_IDT_ENTRIES);



    // Remap the IRQ table so that IRQ 32 and up map to our ISRs. 
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);


    // Set all entries in the IDT to default interrupt handler.
    for (int i = 0; i < NUM_IDT_ENTRIES; i++)
    {
        idt_set_entry(i, (uint32_t)default_isr, 0x08, 0x8E);
    }
    



    // Add ISRs to IDT
    idt_set_entry(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_entry(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_entry(7, (uint32_t)isr7, 0x08, 0x8E);


    // Add IRQs to IDT
    idt_set_entry(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_entry(33, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_entry(34, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_entry(35, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_entry(36, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_entry(37, (uint32_t)irq5, 0x08, 0x8E);
    idt_set_entry(38, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_entry(39, (uint32_t)irq7, 0x08, 0x8E);
    idt_set_entry(40, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_entry(41, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_entry(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_entry(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_entry(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_entry(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_entry(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_entry(47, (uint32_t)irq15, 0x08, 0x8E);


    // Load the IDT into IDT register using the assembly function 'idt_load'.
    idt_load((uint32_t)&idt_pointer);
}