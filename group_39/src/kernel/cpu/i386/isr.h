// From James Molloy's implementation
// found at http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html

#include "interrupts.h"
#include <stdint.h>

// A few defines to make life a little easier
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

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*isr_t)(registers);
void register_interrupt_handler(int n, isr_t handler); 
void irq_handler(registers regs);