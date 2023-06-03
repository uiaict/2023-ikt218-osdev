#include "idt.h"
#include "isr.h"
#include "string.h"



// Array to hold information about registered interrupt handlers
struct idt_entry_t idt[IDT_ENTRIES];
struct idt_ptr_t idt_ptr;
struct int_handler interrupt_handler[IDT_ENTRIES];

extern "C"{
  extern void idt_load(uint32_t);


  extern void isr0();
  extern void isr1();
  extern void isr2();
  extern void isr3();
  extern void isr4();
  extern void isr5();
  extern void isr6();
  extern void isr7();
  extern void isr8();
  extern void isr9();
  extern void isr10();
  extern void isr11();
  extern void isr12();
  extern void isr13();
  extern void isr14();
  extern void isr15();
  extern void isr16();
  extern void isr17();
  extern void isr18();
  extern void isr19();
  extern void isr20();
  extern void isr21();
  extern void isr22();
  extern void isr23();
  extern void isr24();
  extern void isr25();
  extern void isr26();
  extern void isr27();
  extern void isr28();
  extern void isr29();
  extern void isr30();
  extern void isr31();
  extern void irq0 ();
  extern void irq1 ();
  extern void irq2 ();
  extern void irq3 ();
  extern void irq4 ();
  extern void irq5 ();
  extern void irq6 ();
  extern void irq7 ();
  extern void irq8 ();
  extern void irq9 ();
  extern void irq10();
  extern void irq11();
  extern void irq12();
  extern void irq13();
  extern void irq14();
  extern void irq15();
}


void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
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

  set_idt_gate(32, (uint32_t)IRQ0, 0x08, 0x8E);   
  set_idt_gate(33, (uint32_t)IRQ1, 0x08, 0x8E);
  set_idt_gate(34, (uint32_t)IRQ2, 0x08, 0x8E);
  set_idt_gate(35, (uint32_t)IRQ3, 0x08, 0x8E);   
  set_idt_gate(36, (uint32_t)IRQ4, 0x08, 0x8E);
  set_idt_gate(37, (uint32_t)IRQ5, 0x08, 0x8E);
  set_idt_gate(38, (uint32_t)IRQ6, 0x08, 0x8E);   
  set_idt_gate(39, (uint32_t)IRQ7, 0x08, 0x8E);
  set_idt_gate(40, (uint32_t)IRQ8, 0x08, 0x8E);
  set_idt_gate(41, (uint32_t)IRQ9, 0x08, 0x8E);   
  set_idt_gate(42, (uint32_t)IRQ10, 0x08, 0x8E);
  set_idt_gate(43, (uint32_t)IRQ11, 0x08, 0x8E);
  set_idt_gate(44, (uint32_t)IRQ12, 0x08, 0x8E);   
  set_idt_gate(45, (uint32_t)IRQ13, 0x08, 0x8E);
  set_idt_gate(46, (uint32_t)IRQ14, 0x08, 0x8E);   
  set_idt_gate(47, (uint32_t)IRQ15, 0x08, 0x8E);
  
  set_idt_gate(0, (uint32_t)ISR0, 0x08, 0x8E);
  set_idt_gate(1, (uint32_t)ISR1, 0x08, 0x8E);
  set_idt_gate(2, (uint32_t)ISR2, 0x08, 0x8E);
  set_idt_gate(3, (uint32_t)ISR3, 0x08, 0x8E);   
  set_idt_gate(4, (uint32_t)ISR4, 0x08, 0x8E);
  set_idt_gate(5, (uint32_t)ISR5, 0x08, 0x8E);
  set_idt_gate(6, (uint32_t)ISR6, 0x08, 0x8E);   
  set_idt_gate(7, (uint32_t)ISR7, 0x08, 0x8E);
  set_idt_gate(8, (uint32_t)ISR8, 0x08, 0x8E);
  set_idt_gate(9, (uint32_t)ISR9, 0x08, 0x8E);   
  set_idt_gate(10, (uint32_t)ISR10, 0x08, 0x8E);
  set_idt_gate(11, (uint32_t)ISR11, 0x08, 0x8E);
  set_idt_gate(12, (uint32_t)ISR12, 0x08, 0x8E);   
  set_idt_gate(13, (uint32_t)ISR13, 0x08, 0x8E);
  set_idt_gate(14, (uint32_t)ISR14, 0x08, 0x8E);
  set_idt_gate(15, (uint32_t)ISR15, 0x08, 0x8E);   
  set_idt_gate(16, (uint32_t)ISR16, 0x08, 0x8E);
  set_idt_gate(17, (uint32_t)ISR17, 0x08, 0x8E);
  set_idt_gate(18, (uint32_t)ISR18, 0x08, 0x8E);   
  set_idt_gate(19, (uint32_t)ISR19, 0x08, 0x8E);
  set_idt_gate(20, (uint32_t)ISR20, 0x08, 0x8E);
  set_idt_gate(21, (uint32_t)ISR21, 0x08, 0x8E);   
  set_idt_gate(22, (uint32_t)ISR22, 0x08, 0x8E);
  set_idt_gate(23, (uint32_t)ISR23, 0x08, 0x8E);
  set_idt_gate(24, (uint32_t)ISR24, 0x08, 0x8E);   
  set_idt_gate(25, (uint32_t)ISR25, 0x08, 0x8E);
  set_idt_gate(26, (uint32_t)ISR26, 0x08, 0x8E);
  set_idt_gate(27, (uint32_t)ISR27, 0x08, 0x8E);   
  set_idt_gate(28, (uint32_t)ISR28, 0x08, 0x8E);
  set_idt_gate(29, (uint32_t)ISR29, 0x08, 0x8E);
  set_idt_gate(30, (uint32_t)ISR30, 0x08, 0x8E);   
  set_idt_gate(31, (uint32_t)ISR31, 0x08, 0x8E);

  idt_load((uint32_t)&idt_ptr);
}

