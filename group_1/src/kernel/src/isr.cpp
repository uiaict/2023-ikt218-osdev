extern "C"
{
    #include "../include/isr.h"
    #include "system.h"
    #include "../include/common.h"
    #include "keyboard.h"
}

void interrupt_handler_0() {
    printk("\nDivide by zero error!");
}

void interrupt_handler_1() {
    printk("\nDebug exception!");
}

void interrupt_handler_2() {
    printk("\nNon maskable interrupt!");
}

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}


void isr_handler(registers_t regs) {
    switch (regs.int_no) {
        // ... (other cases for different interrupts)
        case 0:
            interrupt_handler_0();
            break;
        case 1:
            interrupt_handler_1();
            break;
        case 2:
            interrupt_handler_2();
            break;
        case 33:
            keyboard_handler();
            break;
        default:
            printk("\nNO, PLEASE GOD NO!");
            break;
    }
}

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

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}
