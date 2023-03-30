/*
This cpp file contains the implementation of the functions that create 
an interupt descriptor table (idt) in our os. The table defines
interupt numbers and points to interupt handling functions that deals
with the issue or reason for the interupt.
*/

#include "interrupts.h"
#include "common.h"
#include <cstddef>
#include "idt.h"

extern "C" {
  // makes the idt_flush assembly function 
  // callable within this file.
  extern void idt_flush(uint32_t); 
}


void init_idt() {
  // Set the IDT limit and get base as the address of the idt
  idt_ptr.limit = sizeof(struct idt_entry_t) * IDT_ENTRIES - 1;
  idt_ptr.base = (uint32_t) &idt;

  
	
  for (int i = 0; i < IDT_ENTRIES; i++) {
    // 1. Initialize the IDT entry to the default interrupt handler
    idt[i].base_low = 0x0000;
    idt[i].base_high = 0x0000;
    idt[i].selector = 0x08;
    idt[i].zero = 0x00;
    idt[i].flags = 0x8E;
    // 2. Initialize the entry in the int_handlers array to NULL
		int_handlers[i].handler = NULL;
  }

  init_interrupts();

  // Load the IDT using asembly (see idt.asm)
  idt_flush((uint32_t)&idt_ptr);
  
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].selector     = sel;
    idt[num].zero = 0;
    idt[num].flags   = flags  | 0x60;
}
