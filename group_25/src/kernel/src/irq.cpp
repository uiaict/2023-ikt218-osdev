#include "idt.h"

#include <cstddef>

#include "system.h"
#include "common.h"
#include "terminal.h"

extern "C" {
    #include "terminal.h"
    void irq_handler(registers_t regs) asm("irq_handler");
}

void init_irq(){
    for (int i = 0; i < IRQ_COUNT; i++){
        irq_handlers[i].data = NULL;
        irq_handlers[i].handler = NULL;
        irq_handlers[i].num = i;
    }
}

void init_irq_handlers(){

    // Enable interrupts
    asm volatile("sti");

    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){

        // Read scancode from keyboard controller
        uint8_t scancode = inb(0x60);

        // Convert scancode to an ASCII character
        if (scancode < sizeof(lower_ascii_codes)) {
            char symbol = lower_ascii_codes[scancode];
            terminal_write_char(symbol);
    }

    }, NULL);
}

void register_irq_handler(int irq, isr_t handler, void *context){
    irq_handlers[irq].handler = handler;
    irq_handlers[irq].data = context;
}

void irq_handler(registers_t regs){
   
    // If int_no >= 40, we must reset the slave as well as the master
    if (regs.int_no >= 40){
        //reset slave
        outb(0xA0, 0x20);
    }
    
    // Interrupt controller
    outb(0x20, 0x20);

    int_handler_t interrupt = irq_handlers[regs.int_no];
    if (interrupt.handler != 0){
        interrupt.handler(&regs, interrupt.data);
    }
}