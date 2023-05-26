#include <hardware_port.h>
#include <system.h>
#include "isr.h"

interrupt_t interrupt_handlers[256];

extern "C"{
    void init_isr() asm("init_isr");
    void irq_handler(registers_t reg) asm("irq_handler");
    void isr_handler(registers_t reg) asm("isr_handler");
}

void init_isr(){
    // Nullify all the interrupt handlers.
    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}

// Registers all 256 handlers
void register_interrupt_handler(uint8_t n, isr_t handler, void* context) {
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
}

void isr_handler(registers_t reg) {
    uint8_t int_no = reg.int_no & 0xFF;
    interrupt_t interrupt = interrupt_handlers[int_no];
    if (interrupt.handler != 0)
    {
        interrupt.handler(&reg, interrupt.context);
    }
    else
    {
        /*monitor_write("unhandled interrupt: ");
        monitor_write_hex(int_no);
        monitor_put('\n');*/
        for(;;);
    }
}

void irq_handler(registers_t reg)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (reg.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    interrupt_t interrupt = interrupt_handlers[reg.int_no];
    if (interrupt.handler != 0)
    {
        interrupt.handler(&reg, interrupt.context);
    }
}