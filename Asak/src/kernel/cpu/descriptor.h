#include <stdint.h>

namespace Asak::CPU::Descriptors {
// Define the GDT entry structure
struct gdt_entry_t {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed));

// Define the IDT entry structure
struct idt_entry_t {
  uint16_t base_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

// Define the GDT and IDT pointers
struct gdt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct idt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

// Initializers
void init_gdt();
void init_idt();

// Gates
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
}

