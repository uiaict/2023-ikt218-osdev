// Written by Group 39 IKT218 Project Spring 2023

#ifndef UIAOS_IDT_H

#define UIAOS_IDT_H

// Include the freestanding stdint library.
#include <stdint.h>

// Number of IDT entries
#define NUM_IDT_ENTRIES 256

struct idt_entry 
{
    uint16_t base_low; // The lower 16 bits of the address
    uint16_t selector; // The segment selector
    uint8_t reserved; // This must always be zero, reserved.
    uint8_t flags; // Flags. 
    uint16_t base_high; // The upper 16 bits of the address. 
} __attribute__((packed));


struct idt_ptr
{
    uint16_t limit; 
    uint32_t base;

} __attribute__((packed));





#endif