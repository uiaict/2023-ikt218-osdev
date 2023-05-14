// Written by Group 39 IKT218 Project Spring 2023

#ifndef UIAOS_IDT_H

#define UIAOS_IDT_H






struct idt_entry 
{
    uint16_t base_low; // The lower 16 bits of the address
    uint16_t selector; // The segment selector
    uint16_t always0; // This must always be zero. 
    uint16_t flags; // Flags. 
    uint16_t base_high; // The upper 16 bits of the address. 
}


struct idt_ptr
{
    uint16_t limit; 
    uint32_t base;

} __attribute__((packed));




#endif UIAOS_IDT_H