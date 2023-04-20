#include "interrupts.h"
#include <stdint.h>
#include <stddef.h>
#include "system.h"

extern "C"{
    void isr_handler(registers_t regs) asm("isr_handler");
}


void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    // This line is important. When the processor extends the 8-bit interrupt number
    // to a 32bit value, it sign-extends, not zero extends. So if the most significant
    // bit (0x80) is set, regs.int_no will be very large (about 0xffffff80).
    uint8_t int_no = regs.int_no & 0xFF;
    int_handler_t intrpt = int_handlers[int_no];
    if (intrpt.handler != 0)
    {

        intrpt.handler(&regs, intrpt.data);
    }
    else
    {
        /*monitor_write("unhandled interrupt: ");
        monitor_write_hex(int_no);
        monitor_put('\n');*/
        printf("unhandled interrupt: %i\n", int_no);
        for(;;);
    }
}

void demo_interrupts()
{
    register_interrupt_handler(ISR1, [](registers_t* regs, void* data)
    {
        printf("ISR1 triggered\n");
    }, NULL);

    register_interrupt_handler(ISR2, [](registers_t* regs, void* data)
    {
        printf("ISR2 triggered\n");
    }, NULL);

    register_interrupt_handler(ISR3, [](registers_t* regs, void* data)
    {
        printf("ISR2 triggered\n");
    }, NULL);
    
}