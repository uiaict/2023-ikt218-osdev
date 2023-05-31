#include "idt.h"

#include <cstddef>

#include "terminal.h"

void isr_handler(registers_t regs) asm("isr_handler");

void register_int_handler(uint8_t n, isr_t handler, void* context){
    int_handlers[n].handler = handler;
    int_handlers[n].data = context;
}

void isr_handler(registers_t regs){
 
    uint8_t int_no = regs.int_no & 0xFF;
    int_handler_t intrpt = int_handlers[int_no];

    if (intrpt.handler != 0){
        // Handle interrupt
        intrpt.handler(&regs, intrpt.data);
    }
    else{
        terminal_write("Unhandled ISR.\n");
    }
}

void init_interrupt_handlers(){
    register_int_handler(ISR3,[](registers_t* regs, void* data){
        terminal_write("Triggered ISR3\n");
    },NULL);
    register_int_handler(ISR4,[](registers_t* regs, void* data){
        terminal_write("Triggered ISR4\n");
    },NULL);
    register_int_handler(ISR5,[](registers_t* regs, void* data){
        terminal_write("Triggered ISR5\n");
    },NULL);
}