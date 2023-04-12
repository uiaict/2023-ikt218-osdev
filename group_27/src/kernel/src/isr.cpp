//
// isr.c
// This code contains interrupt request handlers and service routines
//

#include "common.h"
#include "isr.h"
#include "printing.h"

extern "C" {
    void isr_handler(registers_t);
    void irq_handler(registers_t regs);
}

// Keep track of registered interrupt handlers
struct interrupt_handler_t {
  int num;
  isr_t handler;
  void *data;
};

// Create an array of interrupt handlers
isr_t interrupt_handlers[256];
interrupt_handler_t irq_handlers[16];

// Gets called from interrupt.asm
// Writes the interrupts to the screen
void isr_handler(registers_t regs)
{
    write_to_terminal(1, "recieved interrupt: ");
    write_int_to_terminal(2, regs.int_no);
} 

// Disable interrupts temporarily
asm volatile("sti");

// Gets called from the ASM interrupt handler in interrupt.asm
void irq_handler(registers_t regs)
{
   // Sends an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

    interrupt_handler_t intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.data);
    }
} 

// Register the interrupt handlers
void register_interrupt_handler(u8int n, isr_t handler)
{
  interrupt_handlers[n] = handler;
} 

// Register an IRQ handler
void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}