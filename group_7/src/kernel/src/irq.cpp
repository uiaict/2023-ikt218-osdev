#include "interrupts.h"
#include <cstddef>
#include "common.h"
#include "system.h"

extern "C"{
    /// to make the function callable in asembly as irq_handler.
    /// The function is implemented further down in this file.
    void irq_handler(registers_t regs) asm("irq_handler");
}



/** Initializes all interupt requests. */
void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i].data = NULL;
    irq_handlers[i].handler = NULL;
    irq_handlers[i].num = i;
  }
}

/// Define an interrupt request handler, by assigning a handler to the irq.
void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}

// The main IRQ handler
// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    int_handler_t intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.data);
    }

}