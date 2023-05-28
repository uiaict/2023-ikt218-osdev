#include "isr.h"
#include "common.h"
#include "system.h"
#include  <string.h>
//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//          Based on 
//Hardware Interrupt: Non-maskable interrupt

void triggered_interrupt_error_not_implemented(registers_t regs){
    printf("Other interrupt triggered, not implemented");
}
interrupt_t interrupt_handlers[256];

//void init_isr() asm("init_isr");
//void irq_handler(registers_t regs) asm("irq_handler");
//void isr_handler(registers_t regs) asm("isr_handler");

extern "C"{
    //void init_isr() asm("init_isr");
    void irq_handler(registers_t regs) asm("irq_handler");
    void isr_handler(registers_t regs) asm("isr_handler");
}

void init_isr(){
    // Nullify all the interrupt handlers.
    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
    
}

void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    //ISR to handle the interrupt
    interrupt_handlers[n].handler = handler;
    //enabler for adapting the handler
    interrupt_handlers[n].context = context;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    // This line is important. When the processor extends the 8-bit interrupt number
    // to a 32bit value, it sign-extends, not zero extends. So if the most significant
    // bit (0x80) is set, regs.int_no will be very large (about 0xffffff80).
    uint8_t int_no = regs.int_no & 0xFF;
    interrupt_t intrpt = interrupt_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.context);
    }
    
}

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

    interrupt_t intrpt = interrupt_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.context);
    }

}