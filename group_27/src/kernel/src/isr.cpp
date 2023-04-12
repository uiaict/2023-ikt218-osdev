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
interrupt_handler_t interrupt_handlers[256];
interrupt_handler_t irq_handlers[16];

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    // This line is important. When the processor extends the 8-bit interrupt number
    // to a 32bit value, it sign-extends, not zero extends. So if the most significant
    // bit (0x80) is set, regs.int_no will be very large (about 0xffffff80).
    uint8_t int_no = regs.int_no & 0xFF;
    interrupt_handler_t intrpt = interrupt_handlers[int_no];
    if (intrpt.handler != 0)
    {

        intrpt.handler(&regs, intrpt.data);
    }
    else
    {
        /*monitor_write("unhandled interrupt: ");
        monitor_write_hex(int_no);
        monitor_put('\n');*/
        for(;;);
    }
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


void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].data = context;
}

// Register an IRQ handler
void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}