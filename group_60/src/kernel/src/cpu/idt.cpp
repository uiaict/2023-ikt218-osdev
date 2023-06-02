#include <descriptor_tables.h>
#include <interrupts.h>

// Getting the idt_flush function from assembly
extern "C" {
    extern void idt_flush(uint32_t idt_p);
}

void init_idt() {
    // Set the IDT limit
    idt_p.limit = sizeof(struct idt_entry_t) * IDT_ENTRIES - 1;
    idt_p.base = (uint32_t) &idt;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        // Setting all entries to default values
        idt[i].base_low = 0x0000;
        idt[i].base_high = 0x0000;
        idt[i].selector = 0x08;
        idt[i].zero = 0x00;
        idt[i].flags = 0x8E;

        // Setting the handler to neutral - NULL
	    int_handlers[i].handler = NULL;
    }

    init_interrupts();

    // Load the IDT using asm
    idt_flush((uint32_t) &idt_p);
}

// Setting an entry in the interupt descriptor table (IDT)
void idt_set_gate(uint8_t vector, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[vector].base_low = base & 0xFFFF;
    idt[vector].base_high = (base >> 16) & 0xFFFF;

    idt[vector].selector = sel;
    idt[vector].zero = 0;
    idt[vector].flags = flags  | 0x60;
}

void init_interrupts() {
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

    /* set ISR and IRQ bellow here */
}