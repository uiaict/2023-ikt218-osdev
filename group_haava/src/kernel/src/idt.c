#include "idt.h"

#define NULL_SEGMENT_DESCRIPTOR 0x00
#define INTERRUPT_GATE 0x0E


struct idt_entry idt_ptr[IDT_ENTRIES];

static void idt_set_gate(int num, uint32_t offset, uint16_t selector, uint8_t attribute)
{
    idt_ptr[num].offset_low = offset & 0xFFFF;
    idt_ptr[num].offset_high = offset >> 16;
    idt_ptr[num].selector = selector;

    idt_ptr[num].zero = 0x00;
    idt_ptr[num].attributes = attribute;
}

void idt_init()
{
    struct idt_ptr idt;
    idt.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
    idt.base = (uint32_t) &idt_ptr;

    // Specify all IDT entries to NULL segment descriptor and interrupt gate.
    for (int i = 0; i < IDT_ENTRIES; i++)
        idt_set_gate(i, 0, NULL_SEGMENT_DESCRIPTOR, INTERRUPT_GATE);

    __asm__ __volatile__("lidt %0" : : "m" (idt));
}
