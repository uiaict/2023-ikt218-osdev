#include "idt.h"
#include <stdint.h>
#include "terminal.h"
#include <cstddef>

void isr_handler(registers regs) asm("isr_handler");

void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}

// Called from ASM isr_common_stub
void isr_handler(registers regs)
{
    uint8_t int_no = regs.int_no & 0xFF;
    int_handler intrpt = int_handlers[int_no];

    if (intrpt.handler != 0) {
        intrpt.handler(&regs, intrpt.data);
    }
    else {
        terminal_write("Unhandled interrupt");
    }
}

void init_interrupt_handlers()
{
    register_interrupt_handler(3, [](registers* regs, void* data) {
        terminal_write("Interrupt 3 was triggered");
    }, NULL);
    
    register_interrupt_handler(4, [](registers* regs, void* data) {
        terminal_write("Interrupt 4 was triggered");
    }, NULL);

    register_interrupt_handler(5, [](registers* regs, void* data) {
        terminal_write("Interrupt 5 was triggered");
    }, NULL);
}