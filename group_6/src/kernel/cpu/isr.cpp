#include "isr.h"
#include "memory.h"
#include "hardware_port.h"
#include "../screen/screen.h"

UiAOS::CPU::ISR::interrupt_t interrupt_handlers[256];

extern "C"{
    void init_isr() asm("init_isr");
    void irq_handler(UiAOS::CPU::ISR::registers_t regs) asm("irq_handler");
    void isr_handler(UiAOS::CPU::ISR::registers_t regs) asm("isr_handler");
}

void init_isr(){
    // Nullify all the interrupt handlers.
    // memset(&interrupt_handlers, 0, sizeof(UiAOS::CPU::ISR::isr_t)*256);
    write_string(0xF, "Hello, worldddd!");
}


void UiAOS::CPU::ISR::register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
}




// This gets called from our ASM interrupt handler stub.
void isr_handler(UiAOS::CPU::ISR::registers_t regs)
{
    // This line is important. When the processor extends the 8-bit interrupt number
    // to a 32bit value, it sign-extends, not zero extends. So if the most significant
    // bit (0x80) is set, regs.int_no will be very large (about 0xffffff80).
    uint8_t int_no = regs.int_no & 0xFF;
    UiAOS::CPU::ISR::interrupt_t intrpt = interrupt_handlers[int_no];


    write_string(0xF, "ISR triggered");

    if (intrpt.handler != 0)
    {

        intrpt.handler(&regs, intrpt.context);
    }
    else
    {
        write_string(0xF, "unhandled interrupt: ");
        for(;;);
    }
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(UiAOS::CPU::ISR::registers_t regs)
{
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    UiAOS::CPU::ISR::interrupt_t intrpt = interrupt_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.context);
    }

}