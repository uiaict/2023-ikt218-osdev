extern "C"
{
    #include "../include/isr.h"
    #include "system.h"
    #include "../include/common.h"
    #include "keyboard.h"
}

void divide_by_zero_error(registers_t regs) {
    printk("\nDivide by zero error!");
}

void debug_exception(registers_t regs) {
    printk("\nDebug exception!");
}

void non_maskable_interrupt(registers_t regs) {
    printk("\nNon maskable interrupt!");
}

void default_ISR(registers_t regs)
{
    printk("\nNot Implemented");
}

isr_t interrupt_handlers[256];

void initialize_interrupt_handlers()
{
    for (int i = 0; i < 256; i++) {
        interrupt_handlers[i] = default_ISR;
    }
    interrupt_handlers[0] = divide_by_zero_error;
    interrupt_handlers[1] = debug_exception;
    interrupt_handlers[2] = non_maskable_interrupt;

}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs) {
    isr_t handler = interrupt_handlers[regs.int_no];
    handler(regs);
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
