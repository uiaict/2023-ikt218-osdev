#include <cstddef>
#include "idt.h"

void ESOS::IDT::init_idt() asm ("init_idt");


extern "C" {
  extern void idt_flush(uint32_t);
}

// Array to hold information about registered interrupt handlers
struct ESOS::IDT::int_handler_t int_handlers[IDT_ENTRIES];
struct ESOS::IDT::idt_entry_t idt[IDT_ENTRIES];
struct ESOS::IDT::idt_ptr_t idt_ptr;



void ESOS::IDT::init_idt() {
  // Set the IDT limit
  idt_ptr.limit = sizeof(struct ESOS::IDT::idt_entry_t) * IDT_ENTRIES - 1;
  idt_ptr.base = (uint32_t) &idt;

  // 1. Initialize all IDT entries to the default interrupt handler
	// 2. Initialize all entries in the int_handlers array to NULL
  for (int i = 0; i < IDT_ENTRIES; i++) {
    idt[i].base_low = 0x0000;
    idt[i].base_high = 0x0000;
    idt[i].selector = 0x08;
    idt[i].zero = 0x00;
    idt[i].flags = 0x8E;

	int_handlers[i].handler = NULL;
  }

  // Load the IDT
  idt_flush((uint32_t)&idt_ptr);

}