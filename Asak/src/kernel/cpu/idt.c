#include "descriptor.h"

// Array to hold information about registered interrupt handlers
struct int_handler int_handlers[IDT_ENTRIES];
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idt_ptr;

// Function to register an interrupt handler
void register_int_handler(int num, void (*handler)(void *data), void *data) {
  int_handlers[num].num = num;
  int_handlers[num].handler = handler;
  int_handlers[num].data = data;
}

// The default interrupt handler
void default_int_handler(void *data) {
  // Handle the interrupt
  // ...
}

// The main interrupt handler
void int_handler(int num) {
  // Check if a registered handler exists for this interrupt
  if (int_handlers[num].handler != NULL) {
    int_handlers[num].handler(int_handlers[num].data);
  } else {
    // Call the default interrupt handler if no registered handler exists
    default_int_handler(NULL);
  }
}

void init_idt() {
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

  // Load the IDT
  idt_load(&idt_ptr);
}