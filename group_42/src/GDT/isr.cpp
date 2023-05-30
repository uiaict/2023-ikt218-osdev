

#include "isr.h"
#include "memory.h"
#include "../kernel/src/test.h"

#include "hardware_port.h"

UiAOS::CPU::ISR::interrupt_t interrupt_handlers[256];

extern "C"{
    void init_isr() asm("init_isr");
    void irq_handler(UiAOS::CPU::ISR::registers_t regs) asm("irq_handler");
    void isr_handler(UiAOS::CPU::ISR::registers_t regs) asm("isr_handler");
}

void init_isr(){
    
    memset(&interrupt_handlers, 0, sizeof(UiAOS::CPU::ISR::isr_t)*256);
}


void UiAOS::CPU::ISR::register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
}


void isr_handler(UiAOS::CPU::ISR::registers_t regs)
{
   
    uint8_t int_no = regs.int_no & 0xFF;
    UiAOS::CPU::ISR::interrupt_t intrpt = interrupt_handlers[int_no];
    if (intrpt.handler != 0)
    {
       
        intrpt.handler(&regs, intrpt.context);
    }
    else
    {
      
        write_string(0x0B, "Goodbye");
        for(;;);
    }
}


void irq_handler(UiAOS::CPU::ISR::registers_t regs)
{
    if (regs.int_no >= 40)
    {

        outb(0xA0, 0x20);
    }
    
    outb(0x20, 0x20);

    UiAOS::CPU::ISR::interrupt_t intrpt = interrupt_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.context);
    }

}