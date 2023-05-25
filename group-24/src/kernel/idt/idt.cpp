#include < system.h >
#include "idt.h"



extern "C"{
    extern void idt_load(uint32_t);
}

void init_idt(void)
{

    idt_ptr.limite = sizeof(struct idt_entry_t) * IDT_ENTRIES - 1;
    idt_ptr.base = (uint32_t)&idt;
    /* Init irq */
    for (int i = 0; i < IDT_ENTRIES; i++){
        idt[i].base_low = 0x0000;
        idt[i].base_high = 0x0000;
        idt[i].selector = 0x08;
        idt[i].zero = 0x00;
        idt[i].flags = 0x8E;

        // interrupts handler here
    }

     idt_flush((uint32_t)&idt_ptr);
    
}


void idt_load() {
  // Load the IDT using the LIDT instruction
  asm volatile("lidt %0" : : "m" (idt_ptr));
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector     = sel;
    idt[num].zero = 0;
    idt[num].flags   = flags  | 0x60;
}

//interrupts 