#include "idt.h"
#include <stdint.h>
#include <cstddef>
#include "common.h"

void idt_init() asm("idt_init");

extern "C" {
    extern void idt_flush(uint32_t);
    extern void (*isr_arr[])(void);
}

struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idt_ptr;

void idt_init() {
    idt_ptr.limit = sizeof(idt_entry) * IDT_ENTRIES - 1;
    idt_ptr.base = reinterpret_cast<uint32_t>(&idt);

    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt[i].base_low = 0x0000;
        idt[i].base_high = 0x0000;
        idt[i].selector = 0x08;
        idt[i].always0 = 0x00;
        idt[i].flags = 0x8E;

        int_handlers[i].handler = nullptr;
    }

    init_interrupts();
    init_interrupt_handlers();
    irq_init();
    init_irq_handlers();

    idt_flush(reinterpret_cast<uint32_t>(&idt_ptr));
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags | 0x60;
}

void init_interrupts() {
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

    for (INTERRUPT_SERVICE_ROUTINES i = ISR0; i <= IRQ15; ++i) {
        idt_set_gate(i, reinterpret_cast<uint32_t>(isr_arr[i]), 0x08, 0x8E);
    }
}
