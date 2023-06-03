#include <cstddef>
#include <stdint.h>
#include "idt.h"
#include "terminal.h"
#include "common.h"

extern "C" {
    #include "terminal.h"
    void irq_handler(registers regs) asm("irq_handler"); // External C function
}

// Function to assign a specific handler to an IRQ
void assign_irq_handler(int irq, isr_t handler, void *ctx) 
{
    irq_handlers[irq].handler = handler;
    irq_handlers[irq].data = ctx;
}

// IRQ handler function
void irq_handler(registers regs)
{
    // If int_no >=40, send reset signal to slave
    if (regs.int_no >= 40) write_to_port(0xA0, 0x20);

    // EOI signal to master PIC
    write_to_port(0x20, 0x20);

    // Retrieve interrupt handler
    int_handler intrpt = irq_handlers[regs.int_no];

    // If handler is assigned, execute it
    if (intrpt.handler != 0) intrpt.handler(&regs, intrpt.data);
}

// Initialize all IRQ handlers
void initialize_irq()
{
    for (int i = 0; i < IRQ_COUNT; i++) {
        irq_handlers[i].handler = NULL;
        irq_handlers[i].data = NULL;
        irq_handlers[i].num = i;
    }
}

// Initialize IRQ handlers and enable interrupts
void initialize_irq_handlers()
{
    asm volatile("sti"); // Allow interrupts

    // Set up IRQ1 handler
    assign_irq_handler(IRQ1, [](registers*, void*) 
    {
        uint8_t scancode = read_byte_from_port(0x60);
        if (scancode < sizeof(key_map)) output_char_to_terminal(key_map[scancode]);
    }, NULL);
}
