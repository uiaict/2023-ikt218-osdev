#pragma once
#include <stdint.h>


void idt_init();
void remap_pic();
void enable_interrupts();

typedef struct {
    uint16_t base_low;     // The lower 16 bits of the address to jump to when this interrupt fires
    uint16_t sel;          // Kernel segment selector
    uint8_t  always0;      // This must always be zero
    uint8_t  flags;        // Flags
    uint16_t base_high;    // The upper 16 bits of the address to jump to
} __attribute__((packed)) idt_entry_t;


typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;


