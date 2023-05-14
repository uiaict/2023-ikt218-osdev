// Written by Group 39 IKT218 Project Spring 2023

#include "idt.h"








































void idt_set_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xFFFF; // Set the lower 16 bits of the base address. 
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF; // Set the upper 16 bits of the base address.

    idt_entries[num].sel     = sel; // Set segment selector
    idt_entries[num].always0 = 0; // Set the "alwaays0" field to 0. 
    idt_entries[num].flags   = flags  | 0x60; // Set flags. 
}