#ifndef DESCRIPTOR_TABLES_H
#define DESCRIPTOR_TABLES_H
#include "system.h"
#include "common.h"
#include <stdint.h>
#include <stdbool.h>
#define GDT_ENTRIES 5
#define IDT_ENTRIES 256

void init_descriptor_tables();
struct gdt_entry
{
    uint16_t limit_low;         // The lower 16 bits of the limit.
    uint16_t base_low;          // The lower 16 bits of the base.
    uint8_t base_middle;        // The next 8 bits of the base.
    uint8_t access;             // 8 bits access flag
    uint8_t granularity;        // 8 bits of granularity
    uint8_t base_high;          // The last 8 bits of the base.
} __attribute__((packed));         // so that gcc use as little memory as possible
typedef struct gdt_entry gdt_entry_t;

// Local descriptor table pointer
struct gdt_ptr 
{
    uint16_t limit;              // 16 bit limit. Size of the GDT
    uint32_t base;               // 32 bit pointer. First entry in GDT
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

// define interrupt gate (handler)
struct idt_entry_struct {
  uint16_t base_low;             // lower 16 bits of interrupt service routine
  uint16_t selector;             // GDT segment selector the CPU loads into code segment (CS) register when interrupt fires
  uint8_t zero;                  // unused, set to 0
  uint8_t flags; 
  uint16_t base_high;            // higher 16 bits of ISR, with isr_low, forms 32 bit address of ISR
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

// Define the IDTR table, this a pointer to the array pf interrupt handlers
struct idtr_t_struct {
  uint16_t limit; 
  uint32_t base;
} __attribute__((packed));
typedef struct idtr_t_struct idtr_t;





// acess the ASM functions from C
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


#endif

