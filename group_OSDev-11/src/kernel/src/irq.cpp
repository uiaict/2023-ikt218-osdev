#include "idt.h"
#include "terminal.h"
#include "common.h"
#include <cstddef>
#include <stdint.h>

extern "C" {
    #include "terminal.h"
    void irq_handler(registers regs) asm("irq_handler");  // External C function declaration
}

// Initialize IRQ handlers to default values
void initialize_irq()
{
    for (int i = 0; i < IRQ_COUNT; i++) {
        irq_handlers[i].handler = NULL;
        irq_handlers[i].data = NULL;
        irq_handlers[i].num = i;
    }
}

// Assign a handler to a specific IRQ
void assign_irq_handler(int irq, isr_t handler, void *ctx) 
{
    irq_handlers[irq].handler = handler;
    irq_handlers[irq].data = ctx;
}

// Define the IRQ handler function
void irq_handler(registers regs)
{
    // If interrupt number is >=40, reset signal to slave
    if (regs.int_no >= 40) {
        write_to_port(0xA0, 0x20); 
    }

    // Send End Of Interrupt to master
    write_to_port(0x20, 0x20); 

    // Fetch the interrupt handler
    int_handler intrpt = irq_handlers[regs.int_no];

    // If there is a handler, execute it
    if (intrpt.handler != 0) {
        intrpt.handler(&regs, intrpt.data);
    }
}

// Define a function to initialize IRQ handlers
void initialize_irq_handlers()
{
    // Turn on interrupts
    asm volatile("sti");

    // Register IRQ handler for IRQ1
    assign_irq_handler(IRQ1, [](registers*, void*) 
    {
        // Fetch scancode
        uint8_t scancode = read_byte_from_port(0x60);

        // If scancode is within key_map size, output character to terminal
        if (scancode < sizeof(key_map)) {
            output_char_to_terminal(key_map[scancode]);
        }
    }, NULL);
}
