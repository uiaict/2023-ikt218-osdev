#include "idt.h"
#include <stdint.h>
#include <cstddef>
#include "common.h"

void initialize_idt() asm("initialize_idt");

extern "C" {
    extern void flush_idt(uint32_t);
}

struct idt_entry idt[IDT_ENTRIES];            // IDT entry array
struct idt_pointer idt_pointer;               // IDT pointer structure

void initialize_idt() {

    idt_pointer.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;    // Set the IDT limit based on the size of an IDT entry multiplied by the number of entries
    
    // IDT base address
    idt_pointer.base = (uint32_t) &idt;         // Set the IDT base address to the start of the IDT array


    // Initialize IDT entries
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt[i].base_low = 0x0000;               // Set the low 16 bits of the base address of the IDT entry to 0x0000
        idt[i].base_high = 0x0000;              // Set the high 16 bits of the base address of the IDT entry to 0x0000
        idt[i].selector = 0x08;                  // Set the selector field of the IDT entry to 0x08
        idt[i].always0 = 0x00;                   // Set the 'always0' field of the IDT entry to 0x00
        idt[i].flags = 0x8E;                     // Set the flags field of the IDT entry to 0x8E

        int_handlers[i].handler = NULL;         // Set the interrupt handler for the corresponding IDT entry to NULL
    }

    initialize_interrupts();                          // Initialize interrupts
    initialize_interrupt_handlers();            // Initialize interrupt handlers
    initialize_irq();                                 // Initialize IRQs
    initialize_irq_handlers();                        // Initialize IRQ handlers

    // Load the IDT:
    flush_idt((uint32_t)&idt_pointer);
}

void configure_interrupt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;           // Set the low 16 bits of the base address of the IDT entry
    idt[num].base_high = (base >> 16) & 0xFFFF;  // Set the high 16 bits of the base address of the IDT entry
    idt[num].selector = sel;                     // Set the selector field of the IDT entry
    idt[num].always0 = 0;                        // Set the 'always0' field of the IDT entry
    idt[num].flags = flags | 0x60;               // Set the flags field of the IDT entry
}


// Array of function pointers to the interrupt service routines (ISRs).
void (*isr_functions[32])(void) = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, 
    isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15, 
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23, 
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
};

// Array of function pointers to the interrupt request (IRQ) handlers.
void (*irq_functions[16])(void) = {
    irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, 
    irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15
};

void initialize_interrupts()
{
    // Initiate the Programmable Interrupt Controllers (PICs) with a 4-step initialization sequence.
    write_to_port(0x20, 0x11); // Initialize the master PIC.
    write_to_port(0xA0, 0x11); // Initialize the slave PIC.
    write_to_port(0x21, 0x20); // Set the offset of the master PIC to 0x20.
    write_to_port(0xA1, 0x28); // Set the offset of the slave PIC to 0x28.
    write_to_port(0x21, 0x04); // Tell the master PIC there is a slave PIC at IRQ2.
    write_to_port(0xA1, 0x02); // Tell the slave PIC its cascade identity (IRQ2).
    write_to_port(0x21, 0x01); // Set mode of the master PIC.
    write_to_port(0xA1, 0x01); // Set mode of the slave PIC.
    write_to_port(0x21, 0x0);  // Unmask interrupts on the master PIC.
    write_to_port(0xA1, 0x0);  // Unmask interrupts on the slave PIC.

    // Configure the interrupt gates for the ISRs.
    for(int i = 0; i < 32; i++) {
        configure_interrupt_gate(i, (uint32_t)isr_functions[i], 0x08, 0x8E);
    }

    // Configure the interrupt gates for the IRQ handlers.
    for(int i = 0; i < 16; i++) {
        configure_interrupt_gate(i + 32, (uint32_t)irq_functions[i], 0x08, 0x8E);
    }
}

