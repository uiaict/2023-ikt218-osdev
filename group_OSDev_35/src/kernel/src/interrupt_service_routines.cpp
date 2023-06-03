/*
    code sourced from
    https://github.com/cfenollosa/os-tutorial/blob/master/18-interrupts/cpu/isr.h
    https://github.com/perara/ikt218-advanced-operating-systems/blob/master/src/kernel/cpu/i386/isr.cpp
*/

#include "interrupt_service_routines.h"
#include "common.h"

interrupt_t interrupt_handlers[256];

extern "C"
{
    void init_isr() asm("init_isr");
    void irq_handler(registers_t regs) asm("irq_handler");
    void isr_handler(registers_t regs) asm("isr_handler");
}

void init_isr()
{
    for (int i = 0; i < 256; i++)
    {
        interrupt_handlers[i].handler = nullptr;
        interrupt_handlers[i].context = nullptr;
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler, void *context)
{
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    uint8_t int_no = regs.int_no & 0xFF;
    interrupt_t intrpt = interrupt_handlers[int_no];

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