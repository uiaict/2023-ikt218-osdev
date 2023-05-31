#include "descriptor_tables.h"
#include "isr.h"
#include "memory.h"


// Array to hold information about registered interrupt handlers
struct idt_entry_t idt[IDT_ENTRIES];
struct idt_ptr_t idt_ptr;
struct int_handler interrupt_handler[IDT_ENTRIES];

extern "C"{
  extern void idt_load(uint32_t);
}

void set_idt_gate(int index, uint32_t handler_address, uint16_t selector, uint8_t flags) {
    idt[index].low_base = handler_address & 0xFFFF;
    idt[index].selector = selector;
    idt[index].zero = 0;
    idt[index].flags = flags;
    idt[index].high_base = (handler_address >> 16) & 0xFFFF;
}



void init_idt() {
  // Set the IDT limit
  idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
  idt_ptr.base = (uint32_t) &idt;

  memset(&idt, 0, sizeof(idt_entry_t)*IDT_ENTRIES);

  outb(0x20,0x11);
  outb(0xA0,0x11);
  outb(0x21,0x20);
  outb(0xA1,0x28);
  outb(0x21,0x04);
  outb(0xA1,0x02);
  outb(0x21,0x01);
  outb(0xA1,0x01);
  outb(0x21,0x0);
  outb(0xA1,0x0);
  set_idt_gate(32, (uint32_t)irq0, 0x08, 0x8E);   
  set_idt_gate(33, (uint32_t)irq1, 0x08, 0x8E);
  set_idt_gate(34, (uint32_t)irq2, 0x08, 0x8E);
  set_idt_gate(35, (uint32_t)irq3, 0x08, 0x8E);   
  set_idt_gate(36, (uint32_t)irq4, 0x08, 0x8E);
  set_idt_gate(37, (uint32_t)irq5, 0x08, 0x8E);
  set_idt_gate(38, (uint32_t)irq6, 0x08, 0x8E);   
  set_idt_gate(39, (uint32_t)irq7, 0x08, 0x8E);
  set_idt_gate(40, (uint32_t)irq8, 0x08, 0x8E);
  set_idt_gate(41, (uint32_t)irq9, 0x08, 0x8E);   
  set_idt_gate(42, (uint32_t)irq10, 0x08, 0x8E);
  set_idt_gate(43, (uint32_t)irq11, 0x08, 0x8E);
  set_idt_gate(44, (uint32_t)irq12, 0x08, 0x8E);   
  set_idt_gate(45, (uint32_t)irq13, 0x08, 0x8E);
  set_idt_gate(46, (uint32_t)irq14, 0x08, 0x8E);   
  set_idt_gate(47, (uint32_t)irq15, 0x08, 0x8E);
  
  set_idt_gate(1, (uint32_t)isr1, 0x08, 0x8E);
  set_idt_gate(2, (uint32_t)isr2, 0x08, 0x8E);
  set_idt_gate(3, (uint32_t)isr3, 0x08, 0x8E);   
  set_idt_gate(4, (uint32_t)isr4, 0x08, 0x8E);
  set_idt_gate(5, (uint32_t)isr5, 0x08, 0x8E);
  set_idt_gate(6, (uint32_t)isr6, 0x08, 0x8E);   
  set_idt_gate(7, (uint32_t)isr7, 0x08, 0x8E);
  set_idt_gate(8, (uint32_t)isr8, 0x08, 0x8E);
  set_idt_gate(9, (uint32_t)isr9, 0x08, 0x8E);   
  set_idt_gate(10, (uint32_t)isr10, 0x08, 0x8E);
  set_idt_gate(11, (uint32_t)isr11, 0x08, 0x8E);
  set_idt_gate(12, (uint32_t)isr12, 0x08, 0x8E);   
  set_idt_gate(13, (uint32_t)isr13, 0x08, 0x8E);
  set_idt_gate(14, (uint32_t)isr14, 0x08, 0x8E);
  set_idt_gate(15, (uint32_t)isr15, 0x08, 0x8E);   
  set_idt_gate(16, (uint32_t)isr16, 0x08, 0x8E);
  set_idt_gate(17, (uint32_t)isr17, 0x08, 0x8E);
  set_idt_gate(18, (uint32_t)isr18, 0x08, 0x8E);   
  set_idt_gate(19, (uint32_t)isr19, 0x08, 0x8E);
  set_idt_gate(20, (uint32_t)isr20, 0x08, 0x8E);
  set_idt_gate(21, (uint32_t)isr21, 0x08, 0x8E);   
  set_idt_gate(22, (uint32_t)isr22, 0x08, 0x8E);
  set_idt_gate(23, (uint32_t)isr23, 0x08, 0x8E);
  set_idt_gate(24, (uint32_t)isr24, 0x08, 0x8E);   
  set_idt_gate(25, (uint32_t)isr25, 0x08, 0x8E);
  set_idt_gate(26, (uint32_t)isr26, 0x08, 0x8E);
  set_idt_gate(27, (uint32_t)isr27, 0x08, 0x8E);   
  set_idt_gate(28, (uint32_t)isr28, 0x08, 0x8E);
  set_idt_gate(29, (uint32_t)isr29, 0x08, 0x8E);
  set_idt_gate(30, (uint32_t)isr30, 0x08, 0x8E);   
  set_idt_gate(31, (uint32_t)isr31, 0x08, 0x8E);

  idt_load((uint32_t)&idt_ptr);
}

