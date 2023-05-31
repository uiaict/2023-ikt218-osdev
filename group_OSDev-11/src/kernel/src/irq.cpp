#include "idt.h"
#include "terminal.h"
#include "common.h"
#include <cstddef>
#include <stdint.h>

extern "C" {
    #include "terminal.h"
    void irq_handler(registers regs) asm("irq_handler");
}

void irq_init()
{
    for (int i = 0; i < IRQ_COUNT; i++) {
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

void irq_handler(registers regs)
{
    if (regs.int_no >= 40) {
        outb(0xA0, 0x20); // Send reset signal to slave
    }

    outb(0x20, 0x20); // Send EOI to master

    int_handler intrpt = irq_handlers[regs.int_no];

    if (intrpt.handler != 0) {
        intrpt.handler(&regs, intrpt.data);
    }
}

void init_irq_handlers()
{
    asm volatile("sti"); // Enable interrupts

    // Create IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers*, void*) 
    {
        uint8_t scancode = inb(0x60);

        if (scancode < sizeof(keyboard_map)) {
            char c = keyboard_map[scancode];
            output_char_to_terminal(c);
        }
    }, NULL);
}