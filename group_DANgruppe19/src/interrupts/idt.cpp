#include <cstddef>
#include "idt.h"
#include "isr.h"
#include "irq/irq.h"
#include "../kernel/include/terminal.h"

#define IDT_SIZE 256

idt_entry_t idt_entries[IDT_SIZE];
idt_ptr_t   idt_ptr;

extern "C" void idt_set_gate(uint8_t num, uintptr_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;

    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;

    // Must uncomment the OR below when you get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags = flags /* | 0x60 */;
}

extern "C" void idt_install() {
    asm volatile("lidt (%0)" :: "r" (&idt_ptr));
}



extern "C" void* custom_memset(void* ptr, int value, size_t num) {
    unsigned char* buf = reinterpret_cast<unsigned char*>(ptr);
    for (size_t i = 0; i < num; ++i) {
        buf[i] = static_cast<unsigned char>(value);
    }
    return ptr;
}


void idt_init() {

    idt_ptr.limit = (sizeof(idt_entry_t) * IDT_SIZE) - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // Clear out the IDT
    custom_memset(&idt_entries, 0, sizeof(idt_entry_t) * IDT_SIZE);
    //memset(&idt_entries, 0, sizeof(idt_entry_t) * IDT_SIZE);


    // Fill the IDT with your ISRs
    idt_set_gate(0, (uintptr_t)isr0, 0x08, 0x8E);  // Divide by Zero Exception
    //idt_set_gate(6, (uintptr_t)isr1, 0x08, 0x8E);  // Invalid Opcode Exception
    //idt_set_gate(13, (uintptr_t)isr2, 0x08, 0x8E); // General Protection Fault
    idt_set_gate(3, (uintptr_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uintptr_t)isr4, 0x08, 0x8E);


    // Fill the IDT with your IRQs
    idt_set_gate(32, (uintptr_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uintptr_t)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uintptr_t)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uintptr_t)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uintptr_t)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uintptr_t)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uintptr_t)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uintptr_t)irq7, 0x08, 0x8E);

    idt_set_gate(40, (uintptr_t)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uintptr_t)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uintptr_t)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uintptr_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uintptr_t)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uintptr_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uintptr_t)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uintptr_t)irq15, 0x08, 0x8E);


    // Load the IDT using the lidt instruction
    idt_install();
    
}




void remap_pic() {
    // Send initialization command to PICs
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // Remap the IRQs
    outb(0x21, 0x20); // Master PIC starts at interrupt 0x20 (32)
    outb(0xA1, 0x28); // Slave PIC starts at interrupt 0x28 (40)

    // Tell master PIC about the slave PIC
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // Set PICs to 8086 mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Unmask IRQ1 for keyboard input
    //outb(0x21, inb(0x21) & 0xFD);

    // Enable all IRQs
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

}
