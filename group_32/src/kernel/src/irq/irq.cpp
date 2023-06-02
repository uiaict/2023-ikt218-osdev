#include "../interrupts.h"
#include <cstddef>
#include "../common.h"
#include "../screen/screen.h"

/*https://github.com/perara-lectures/ikt218-osdev/blob/master/group_per-arne/src/kernel/src/cpu/irq.cpp*/

extern "C"{
    void irq_handler(registers_t regs) asm("irq_handler");
}



// Initialize IRQ handlers
void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i].data = NULL;
    irq_handlers[i].handler = NULL;
    irq_handlers[i].num = i;
  }
  screenWrite("Initialized IRQ!\n");
}

// Register an IRQ handler
void register_irq_handler(int irq, isr_t handler, void* ctx) {
  irq_handlers[irq].handler = handler;
  irq_handlers[irq].data = ctx;
}

// The main IRQ handler
// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
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

    int_handler_t intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.data);
    }

}

void init_keyboard_handler()
{
     // Enable interrupts
    asm volatile("sti");


    // Create an IRQ handler for IRQ1
    register_irq_handler(IRQ1, [](registers_t*, void*){


        //Read the scancode from the keyboard controller
        uint8_t scancode = inb(0x60);


        // If the scancode is valid, convert it to an ASCII character
        if (scancode < sizeof(ascii_letter))
        {

            char c = ascii_letter[scancode];
            screenPutchar(c);

        }


        // Disable interrupts
        asm volatile ("cli");

    }, NULL);

}

