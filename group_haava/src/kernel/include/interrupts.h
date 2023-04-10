#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

#include "idt.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
#define IRQ_COUNT 16

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();

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

struct registers {
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize IDT.
 *
 * For now we only initialize the NULL, code and data segment.
 */
void idt_init();

/**
 * @brief Initialize IRQ.
 */
void irq_init();

typedef void (*isr_t)(struct registers*);


/** Holds information about an interrupt handler */
struct int_handler {
    int num;
    isr_t handler;
};

// Define an interrupt handler
void register_irq_handler(uint8_t n, isr_t handler);
void register_interrupt_handler(uint8_t n, isr_t handler);


static struct int_handler int_handlers[IDT_ENTRIES];
static struct int_handler irq_handlers[IRQ_COUNT];

#ifdef __cplusplus
};
#endif

#endif /* INTERRUPTS_H */
