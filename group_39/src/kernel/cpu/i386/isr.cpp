#include "interrupts.h"
#include "isr.h"
#include "../../common/common.h"



void irq_handler(registers regs) asm ("irq_handler");

isr_t interrupt_handlers[256];

// Modified version of James Molloy's implementation
// found at http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html
void irq_handler(registers regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.interrupt_number >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.interrupt_number] != 0)
   {
       isr_t handler = interrupt_handlers[regs.interrupt_number];
       handler(regs);
   }
}


void register_interrupt_handler(int n, isr_t handler)
{
  interrupt_handlers[n] = handler;
} 