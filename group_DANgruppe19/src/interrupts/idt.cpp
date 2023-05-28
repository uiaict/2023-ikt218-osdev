#include <cstddef>
#include "idt.h"
#include "isr.h"

#define IDT_SIZE 256

idt_entry_t idt_entries[IDT_SIZE];
idt_ptr_t   idt_ptr;

extern "C" void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
extern "C" void idt_install();


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
    idt_set_gate(32, (uintptr_t)isr0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)isr2, 0x08, 0x8E);

    // Load the IDT using the lidt instruction
    idt_install();
}

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
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

    // Enable all IRQs
    outb(0x21, 0x00);
    outb(0xA1, 0x00);
}
