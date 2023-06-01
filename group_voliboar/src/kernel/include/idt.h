#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

// Define the IDT entry structure
struct idt_entry_t
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

// Define the IDT pointer structure
struct idt_ptr_t
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void init_idt();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_load();

#endif

// SOURCE:
// https://github.com/perara-lectures/ikt218-osdev/blob/c7a80911314076041d4b5c8ec215d0acc963aa0e/group_per-arne/src/kernel/include/descriptor_tables.h