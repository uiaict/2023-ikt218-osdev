#include "idt.h"
#include "system.h"
#include "common.h"
#include <cstddef>

extern "C" 
{
    void irq_handler(ESOS::IDT::registers_t regs) asm("irq_handler");
}
void ESOS::IDT::init_irq()
{
    for (int i = 0; i < IRQ_COUNT; i++)
    {
        ESOS::IDT::irq_handlers[i].data = NULL;
        ESOS::IDT::irq_handlers[i].handler = NULL;
        ESOS::IDT::irq_handlers[i].num = i;
    }
}

void ESOS::IDT::register_irq_handler(int irq, ESOS::IDT::isr_t handler, void *ctx)
{
    ESOS::IDT::irq_handlers[irq].handler = handler;
    ESOS::IDT::irq_handlers[irq].data = ctx;
}

void irq_handler(ESOS::IDT::registers_t regs)
{
    // If the IDT entry that was invoked was greater than 40
    // (meaning IRQ8 - 15), then we need to send an EOI to
    // the slave controller
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // In either case, we need to send an EOI to the master
    // interrupt controller too.
    outb(0x20, 0x20);

    ESOS::IDT::int_handler_t intrpt = ESOS::IDT::irq_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.data);
    }
}

void ESOS::IDT::init_irq_handlers()
{
    // Enable interrupts
    asm volatile("sti");

    // Create an IRQ handler for IRQ1
    ESOS::IDT::register_irq_handler(IRQ1, [](ESOS::IDT::registers_t*, void*){
        printf("Yes we are going on!");

    }, NULL);

    // Disable interrupts
    //asm volatile("cli");
}