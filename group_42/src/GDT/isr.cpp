// file coppied form given repository
#include "isr.h"
#include "memory.h"
#include "../kernel/src/test.h"

#include "hardware_port.h"

UiAOS::CPU::ISR::interrupt_t interrupt_handlers[256];

extern "C"{ // gjør en rekke funkjsoner tilgjenglig i assambly
    void init_isr() asm("init_isr");
    void irq_handler(UiAOS::CPU::ISR::registers_t regs) asm("irq_handler");
    void isr_handler(UiAOS::CPU::ISR::registers_t regs) asm("isr_handler");
}

void init_isr(){ // setter opp Interupt servise rutines
    
    memset(&interrupt_handlers, 0, sizeof(UiAOS::CPU::ISR::isr_t)*256); // sets the adress of all interupthandles to be zero
}


void UiAOS::CPU::ISR::register_interrupt_handler(uint8_t n, isr_t handler, void* context) // conects the given interupt handler to the given interupt
{
    interrupt_handlers[n].handler = handler; 
    interrupt_handlers[n].context = context;
}


void isr_handler(UiAOS::CPU::ISR::registers_t regs) // this function is trigered when an interupt is triggerd
{
   
    uint8_t int_no = regs.int_no & 0xFF; // important line  for extetions ressons
    UiAOS::CPU::ISR::interrupt_t intrpt = interrupt_handlers[int_no];  // the interupt is retrived from a array
    if (intrpt.handler != 0) // if there is a defined handler use the handler
    {
       
        intrpt.handler(&regs, intrpt.context);
    }
    else // if there is no handler inform on the screen what has happend and enter an endless loop
    {
      
        write_string(0x0B, "Goodbye");
        for(;;);
    }
}


void irq_handler(UiAOS::CPU::ISR::registers_t regs) // this function is triggered when an inerupt occors
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