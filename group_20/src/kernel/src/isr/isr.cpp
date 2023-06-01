#include "idt.h"
#include <stdio.h>

extern "C"{
    #include "screen.h"
}

void isr_handler(registers_t regs) asm("isr_handler");


void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}



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
        for(;;);
    }
}


void create_interrupt_handlers() {
    // Create some interrupt handler for 2
    register_interrupt_handler(2,[](registers_t* regs, void* context){
        screenWrite("Interrupt 2 - OK");
    }, NULL);

    // Create some interrupt handlers for 3
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        screenWrite("Interrupt 3 - OK");
    }, NULL);

    // Create some interrupt handler for 4
    register_interrupt_handler(4,[](registers_t* regs, void* context){
        screenWrite("Interrupt 4 - OK");
    }, NULL);
}


// SOURCES: https://github.com/uiaict/ikt218-osdev/pull/1

