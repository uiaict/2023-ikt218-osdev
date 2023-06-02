#include "idt.h"
#include "int.h"
#include "system.h"
#include "common.h"
#include <cstddef>
#include "screen.h"

extern "C" 
{
    void irq_handler(registers_t regs) asm("irq_handler");
}

void init_irq()
{
    for (int i = 0; i < IRQ_COUNT; i++)
    {
        irq_handlers[i].data = NULL;
        irq_handlers[i].handler = NULL;
        irq_handlers[i].num = i;
    }
}

void register_irq_handler(int irq, isr_t handler, void *ctx)
{
    irq_handlers[irq].handler = handler;
    irq_handlers[irq].data = ctx;
}

void irq_handler(registers_t regs)
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

    int_handler_t intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.data);
    }
}

void init_irq_handlers()
{
     // Enable interrupts
    asm volatile("sti");

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){

        //Read the scancode from the keyboard controller
        uint8_t scancode = inb(0x60);

        // If the scancode is valid, convert it to an ASCII character
        if (scancode < sizeof(scancode_to_ascii))
        {
            char c = scancode_to_ascii[scancode];
            terminal_putchar(c);
        }
        
        // Disable interrupts
        asm volatile ("cli");
    }, NULL);
}

// SOURCE:
// https://github.com/perara-lectures/ikt218-osdev/blob/c7a80911314076041d4b5c8ec215d0acc963aa0e/group_per-arne/src/kernel/src/cpu/irq.cpp