#include "idt.h"

extern "C" {
  extern void idt_flush(uint32_t);
}

// Array to hold information about registered interrupt handlers
struct ESOS::IDT::int_handler int_handlers[IDT_ENTRIES];
struct ESOS::IDT::idt_entry idt[IDT_ENTRIES];
struct ESOS::IDT::idt_ptr idt_ptr;



void ESOS::IDT::init_idt() {
  // Set the IDT limit
  idt_ptr.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
  idt_ptr.base = (uint32_t) &idt;

  // 1. Initialize all IDT entries to the default interrupt handler
	// 2. Initialize all entries in the int_handlers array to NULL
  for (int i = 0; i < IDT_ENTRIES; i++) {
    idt[i].base_low = 0x0000;
    idt[i].base_high = 0x0000;
    idt[i].segment = 0x08;
    idt[i].zero = 0x00;
    idt[i].flags = 0x8E;

	int_handlers[i].handler = NULL;
  }

  init_interrupts();

  // Load the IDT
  idt_flush((uint32_t)&idt_ptr);

}