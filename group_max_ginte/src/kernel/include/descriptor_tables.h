#include <stdint.h>

#define GDT_ENTRIES 5
#define IDT_ENTRIES 256

// Define the GDT entry structure
struct gdt_entry {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed));


// Define the IDT entry structure
struct idt_entry {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

// Define the GDT and IDT pointers

struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));


void init_gdt();
void init_idt();

// Load the GDT and IDT

void gdt_load(struct gdt_ptr *gdt_ptr);
void idt_load(struct idt_ptr *idt_ptr);

// Define an interrupt handler
//void interrupt_handler();int_handlers;


void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);