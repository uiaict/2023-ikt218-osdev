#pragma once
#include <stdint.h>


void idt_init();

typedef struct {
  uint16_t base_low;
  uint16_t selector;
  uint8_t  always0;
  uint8_t  flags;
  uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;
