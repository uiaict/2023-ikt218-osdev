#ifndef IDT
#define IDT

#include <stdint.h>

#define IDT_ENTRIES 256

struct idt_entry_t {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

struct idt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

// Function that starts the IDT
void start_idt();


void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

static idt_entry_t idt[IDT_ENTRIES];
static idt_ptr_t idt_ptr;

#endif

// SOURCES: https://github.com/uiaict/ikt218-osdev/pull/1

