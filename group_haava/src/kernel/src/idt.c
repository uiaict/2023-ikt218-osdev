#include "idt.h"

#define KERNEL_CODE_SEGMENT_DESCRIPTOR 0x08
#define NULL_SEGMENT_DESCRIPTOR 0x00
#define INTERRUPT_GATE 0x0E
#define ENABLE_IDT_DESCRIPTOR 0x80

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();

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

    idt_set_gate(0, (uint32_t)isr0, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(1, (uint32_t)isr1, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(2, (uint32_t)isr2, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(3, (uint32_t)isr3, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(4, (uint32_t)isr4, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(5, (uint32_t)isr5, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(6, (uint32_t)isr6, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(7, (uint32_t)isr7, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);

    __asm__ __volatile__("lidt %0" : : "m" (idt));
}
