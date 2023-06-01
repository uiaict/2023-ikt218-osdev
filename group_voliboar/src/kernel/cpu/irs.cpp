#include "idt.h"
#include "screen.h"


void ESOS::IDT::isr_handler(registers_t regs) asm("isr_handler");


void ESOS::IDT::register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    ESOS::IDT::int_handlers[n].handler = handler;
    ESOS::IDT::int_handlers[n].data = context;
}

// This gets called from our ASM interrupt handler stub.
void ESOS::IDT::isr_handler(registers_t regs)
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
        terminal_writestring("Unhandled interrupt");
    }
}

void ESOS::IDT::init_interrupt_handlers()
{
    ESOS::IDT::register_interrupt_handler(3,[](ESOS::IDT::registers_t* regs, void* data){
        terminal_writestring("Interrupt 3 was triggered");
    },NULL);
    ESOS::IDT::register_interrupt_handler(4,[](ESOS::IDT::registers_t* regs, void* data){
        terminal_writestring("Interrupt 4 was triggered");
    },NULL);
    ESOS::IDT::register_interrupt_handler(5,[](ESOS::IDT::registers_t* regs, void* data){
        terminal_writestring("Interrupt 5 was triggered");
    },NULL);
}