#include <cstdint>  // Include standard library for integer types
#include "idt.h"  // Include the header file that contains the definitions of idt_entry and idt_ptr

#define IDT_ENTRIES 256  // Define the number of entries in the IDT. x86 architecture requires 256

void init_idt() asm ("init_idt");  // Declare the function init_idt() which will be linked with the assembler label "init_idt"

idt_entry idt_entries[IDT_ENTRIES];  // Declare an array of idt_entry objects. This will serve as the IDT itself
idt_ptr idt_pointer;  // Declare an idt_ptr which will point to the IDT and its limit

// Declare a function to set an entry in the IDT
void idt_set_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;  // Set the lower 16 bits of the base address
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;  // Set the higher 16 bits of the base address
    idt_entries[num].selector = sel;  // Set the selector field
    idt_entries[num].reserved = 0;  // Set the reserved field to 0
    idt_entries[num].flags = flags | 0x60;  // Set the flags field, setting the two high bits (which are the descriptor privilege level - DPL) to 11 (0x60)
}

// Declare a function to initialize the IDT
void init_idt() {
    idt_pointer.base = (uint32_t)&idt_entries;  // Set the base address of the IDT pointer to the address of the IDT entries
    idt_pointer.limit = sizeof(idt_entry) * IDT_ENTRIES - 1;  // Set the limit of the IDT to the size of all entries minus one

    // Inline assembly to load the IDT pointer into the IDT register (IDTR) of the processor
    __asm__ __volatile__("lidt %0" : : "m" (idt_pointer));
}
