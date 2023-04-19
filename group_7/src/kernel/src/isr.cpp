#include "interrupts.h"
#include <stdint.h>
#include <stddef.h>
#include "system.h"

extern "C"{
    /// To make the function calleable from assembly code as isr_handler.
    /// The function is implemented further down in this file.
    void isr_handler(registers_t regs) asm("isr_handler");
}

/// Define an interrupt handler and add it to the list of interrupt handlers.
void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    /// This line is important. When the processor extends the 8-bit interrupt number
    /// to a 32bit value, it sign-extends, not zero extends. So if the most significant
    /// bit (0x80) is set, regs.int_no will be very large (about 0xffffff80).
    uint8_t int_no = regs.int_no & 0xFF;
    // get the interrupt handler...
    int_handler_t intrpt = int_handlers[int_no];
    if (intrpt.handler != 0)
    {
        // if the handler exists, give it access to the CPU registers.
        intrpt.handler(&regs, intrpt.data);
    }
    else
    {
        
        printf("unhandled interrupt: %i\n", int_no);
        for(;;);
    }
}