#ifndef IDT
#define IDT

#include <stdint.h>
#include <cstddef>
#include "gdt.h"
#include "idt.h"
#include "common.h"

#define IDT_ENTRIES 256

#define ISR1 1
#define ISR2 2
#define ISR3 3
#define ISR4 4
#define ISR5 5
#define ISR6 6
#define ISR7 7
#define ISR8 8
#define ISR9 9
#define ISR10 10
#define ISR11 11
#define ISR12 12
#define ISR13 13
#define ISR14 14
#define ISR15 15
#define ISR16 16
#define ISR17 17
#define ISR18 18
#define ISR19 19
#define ISR20 20
#define ISR21 21
#define ISR22 22
#define ISR23 23
#define ISR24 24
#define ISR25 25
#define ISR26 26
#define ISR27 27
#define ISR28 28
#define ISR29 29
#define ISR30 30
#define ISR31 31

extern "C"{
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
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

/*
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
*/

}

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


typedef struct registers
{
    uint32_t ds;                                                // Data segment selector
    uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax;  // Pushed by pusha.
    uint32_t int_no, err_code;                                  // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, esp, ss;                          // Pushed by the processor automatically.
} registers_t;

typedef void (*isr_t)(registers_t*, void*);

// Structure to hold information about an interrupt handler
struct int_handler_t {
  int num;
  isr_t handler;
  void *data;
};


void init_interrupts();
void start_idt();                                                               // Function that starts the IDT
void set_idt_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void register_interrupt_handler(uint8_t n, isr_t handler, void*);
void isr_handler(registers_t regs);
void create_interrupt_handlers();

static idt_entry_t idt[IDT_ENTRIES];
static idt_ptr_t idt_ptr;
static int_handler_t int_handlers[IDT_ENTRIES];

#endif

// SOURCES: https://github.com/uiaict/ikt218-osdev/pull/1

