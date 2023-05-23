// Written by Group 39 IKT218 Project Spring 2023

#include "idt.h"

idt_entry idt_entries[3];


void idt_set_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_low = base & 0xFFFF; // Set the lower 16 bits of the base address. 
    idt_entries[num].base_high = (base >> 16) & 0xFFFF; // Set the upper 16 bits of the base address.

    idt_entries[num].selector = sel; // Set segment selector
    idt_entries[num].reserved = 0; // Set the "alwaays0" field to 0. 
    idt_entries[num].flags   = flags  | 0x60; // Set flags. 
}