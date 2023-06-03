//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//          Part of this code is modified from Bran's kernel development tutorials.
//          Rewritten for JamesM's kernel development tutorials.
//

#include "isr.h"

UiAOS::CPU::ISR::interrupt_t interrupt_handlers[256];

extern "C"{
    void init_isr() asm("init_isr");
    void irq_handler(UiAOS::CPU::ISR::registers_t regs) asm("irq_handler");
    void isr_handler(UiAOS::CPU::ISR::registers_t regs) asm("isr_handler");
}

void init_isr(){
    // Nullify all the interrupt handlers.
    memset(&interrupt_handlers, 0, sizeof(UiAOS::CPU::ISR::isr_t)*256);
}