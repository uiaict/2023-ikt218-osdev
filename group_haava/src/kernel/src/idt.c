#include <stddef.h>

#include "common.h"
#include "idt.h"
#include "interrupts.h"

#define KERNEL_CODE_SEGMENT_DESCRIPTOR 0x08
#define NULL_SEGMENT_DESCRIPTOR 0x00
#define INTERRUPT_GATE 0x0E
#define ENABLE_IDT_DESCRIPTOR 0x80


struct idt_entry idt_ptr[IDT_ENTRIES];

static void idt_set_gate(int num, uint32_t offset, uint16_t selector, uint8_t attribute)
{
    idt_ptr[num].offset_low = offset & 0xFFFF;
    idt_ptr[num].offset_high = offset >> 16;
    idt_ptr[num].selector = selector;

    idt_ptr[num].zero = 0x00;
    idt_ptr[num].attributes = attribute;
}

static void init_interrupts()
{
    /* Initialize the PIC and remap the IRQ table. */
    output_to_port(PIC1_CMD, 0x11);
    output_to_port(PIC2_CMD, 0x11);
    output_to_port(PIC1_DATA, 0x20);
    output_to_port(PIC2_DATA, 0x28);
    output_to_port(PIC1_DATA, 0x04);
    output_to_port(PIC2_DATA, 0x02);
    output_to_port(PIC1_DATA, 0x01);
    output_to_port(PIC2_DATA, 0x01);
    output_to_port(PIC1_DATA, 0x0);
    output_to_port(PIC2_DATA, 0x0);

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

    idt_set_gate(32, (uint32_t)irq0, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(33, (uint32_t)irq1, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(34, (uint32_t)irq2, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(35, (uint32_t)irq3, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(36, (uint32_t)irq4, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(37, (uint32_t)irq5, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(38, (uint32_t)irq6, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(39, (uint32_t)irq7, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(40, (uint32_t)irq8, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(41, (uint32_t)irq9, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(42, (uint32_t)irq10, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(43, (uint32_t)irq11, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(44, (uint32_t)irq12, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(45, (uint32_t)irq13, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(46, (uint32_t)irq14, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
    idt_set_gate(47, (uint32_t)irq15, KERNEL_CODE_SEGMENT_DESCRIPTOR,
                 ENABLE_IDT_DESCRIPTOR | INTERRUPT_GATE);
}

void idt_init()
{
    struct idt_ptr idt;
    idt.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
    idt.base = (uint32_t) &idt_ptr;

    // Specify all IDT entries to NULL segment descriptor and interrupt gate.
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, NULL_SEGMENT_DESCRIPTOR, INTERRUPT_GATE);
        int_handlers[i].handler = NULL;
    }

    init_interrupts();

    __asm__ __volatile__("lidt %0" : : "m" (idt));
}
