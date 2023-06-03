#include "terminal.h"
#include <cstddef>
#include "idt.h"
#include <stdint.h>

// Forward declaration
void isr_handler(registers regs) asm("isr_handler");

// Assigns a handler function to a specific interrupt
void assign_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}

// Initializes the interrupt handlers
void initialize_interrupt_handlers()
{
    assign_interrupt_handler(3, [](registers* regs, void* data) {
        write_to_terminal("Interrupt 3 has been triggered!");
    }, NULL);

    assign_interrupt_handler(4, [](registers* regs, void* data) {
        write_to_terminal("Interrupt 4 has been triggered!");
    }, NULL);

    assign_interrupt_handler(5, [](registers* regs, void* data) {
        write_to_terminal("Interrupt 5 has been triggered!");
    }, NULL);
}

// Handles ISR; called from the assembly interrupt handler stub
void isr_handler(registers regs)
{
    uint8_t int_no = regs.int_no & 0xFF;
    int_handler intrpt = int_handlers[int_no];

    if (intrpt.handler != 0) {
        intrpt.handler(&regs, intrpt.data);
    } else {
        write_to_terminal("Interrupt not handled.");
    }
}

