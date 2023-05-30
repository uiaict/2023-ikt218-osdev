#include <hardware_port.h>
#include <system.h>
#include "isr.h"
#include <screen.h>

// Set up handlers
interrupt_t interrupt_handlers[256];

extern "C"{
    void init_isr() asm("init_isr");
    void irq_handler(registers_t reg) asm("irq_handler");
    void isr_handler(registers_t reg) asm("isr_handler");
}


// Initialize ISR
void init_isr(){
    // Nullify all the interrupt handlers.
    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
    print("ISR's initialized.\n");
}

// Can register all handlers
void register_interrupt_handler(uint8_t n, isr_t handler, void* context) {
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
}

void register_all_interrupt_handlers() {
    register_interrupt_handler(2,[](registers_t* regs, void* context)
    {
        print("Hello! It's me, Mr.Interrupt 2");
    }, NULL);
    register_interrupt_handler(3,[](registers_t* regs, void* context)
    {
        print("Hello! It's me, Mr.Interrupt 3");
    }, NULL);
}

void isr_handler(registers_t reg) {
    uint8_t int_no = reg.int_no & 0xFF;
    interrupt_t interrupt = interrupt_handlers[int_no];

    print("Recieved Interrupt! ");

    if (interrupt.handler != NULL)
    {
        interrupt.handler(&reg, interrupt.context);
    }
    else
    {
        print("Error! No registered interrupt handler");
    }
}

// The IRQ follows the same layout as ISR here, codewise.

void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i].data = NULL;
    irq_handlers[i].handler = NULL;
    irq_handlers[i].num = i;
  }
  print("IRQ's initialized.\n");
}

void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}

void register_all_irq_handlers() {
    
}

void irq_handler(registers_t reg)
{
    print("Recieved Interrupt request! ");
    
    if (reg.int_no >= 40)
    {
        outb(0xA0, 0x20);
    }
    // Send reset signal
    outb(0x20, 0x20);

    interrupt_t interrupt = interrupt_handlers[reg.int_no];
    if (interrupt.handler != NULL)
    {
        interrupt.handler(&reg, interrupt.context);
    }
    else
    {
        print("Error! No registered IRQ handler");
    }
}
