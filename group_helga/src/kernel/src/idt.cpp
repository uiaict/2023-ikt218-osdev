
#include "idt.h"
#include "isr.h"
#include <cstring>


void init_idt() asm ("init_idt");
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

extern "C"{
    void idt_flush(uint32_t);

    // These extern directives let us access the addresses of our ASM ISR handlers.
    extern void isr0 ();
    extern void isr1 ();
    extern void isr2 ();
    extern void isr3 ();
    extern void isr4 ();
    extern void isr5 ();
    extern void isr6 ();
    extern void isr7 ();
    extern void isr8 ();
    extern void isr9 ();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr20();
    extern void isr21();
    extern void isr22();
    extern void isr23();
    extern void isr24();
    extern void isr25();
    extern void isr26();
    extern void isr27();
    extern void isr28();
    extern void isr29();
    extern void isr30();
    extern void isr31();
    extern void irq0 ();
    extern void irq1 ();
    extern void irq2 ();
    extern void irq3 ();
    extern void irq4 ();
    extern void irq5 ();
    extern void irq6 ();
    extern void irq7 ();
    extern void irq8 ();
    extern void irq9 ();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();

    void* memset(void* ptr, int value, size_t num) {
    unsigned char* buf = (unsigned char*) ptr;
    for (size_t i = 0; i < num; i++)
        buf[i] = (unsigned char)value;
    return ptr;
}
}


idt_entry_t idt_entries[NUM_IDT_ENTRIES];
idt_ptr_t   idt_ptr;

// Set the value of one IDT entry.
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
}

extern void idt_flush(uint32_t);

void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * NUM_IDT_ENTRIES - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // nullify the idt table
    memset(&idt_entries, 0, sizeof(idt_entry_t)*NUM_IDT_ENTRIES);

    // nullify the idt table
    memset(&idt_entries, 0, sizeof(idt_entry_t)*NUM_IDT_ENTRIES);

    // Set ISRs for all the CPU exceptions
    idt_set_gate( 0, (uint32_t)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (uint32_t)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (uint32_t)isr2 , 0x08, 0x8E);
    // ...
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    // Set IRQs for hardware interrupts
    idt_set_gate(32, (uint32_t)irq0 , 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1 , 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2 , 0x08, 0x8E);
    // ...
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

    
    idt_flush((uint32_t)&idt_ptr);
}