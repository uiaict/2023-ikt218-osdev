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
  uint16_t base_low;  // The lower 16 bits of the ISR's address
  uint16_t selector;  // The GDT segment selector that the CPU will load into CS before calling the ISR
  uint8_t zero;       // Set to zero
  uint8_t flags;      // Type and attributes
  uint16_t base_high; // The higher 16 bits of the ISR's address
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

// Gates for GDT and IDT
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
}
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

void irq_remapper();
void gate_setter();