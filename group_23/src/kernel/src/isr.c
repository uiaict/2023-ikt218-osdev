#include "../include/isr.h"
#include "../include/monitor.h"
#include "../include/common.h"

isr_t interrupt_handlers[ISR_SIZE];                             // array of 256 interrupt handlers



// exception messages stored in array
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


//called from ASM interrupt handler stubs
void isr_handler(registers_t regs)                              // takes in the structure regs as argument, prints the interrupt number and the exception message
{
    //clear_screen();

    monitor_write("recieved interrupt: ");
    monitor_write_dec(regs.int_no);
    monitor_put('\n');
    monitor_write("Exception message: ");
    monitor_write(exception_messages[regs.int_no]);
    monitor_put('\n');
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    
}
void register_interrupt_handler(uint8_t num, isr_t handler)     // registers an interrupt handler for a given interrupt number
{
  interrupt_handlers[num] = handler;
}


void irq_handler(registers_t regs)                              // called when IRQ (hardware interrupt) occurs
{

    if (regs.int_no >= 40)                                     // interrupt number > 40, slave PIC
    {
        
        outb(0xA0, 0x20);                                      // send EOI (end of interrupt) signal to slave PIC
    }
    
    outb(0x20, 0x20);                                          // send EOI signal to master PIC

    if (interrupt_handlers[regs.int_no] != 0)                  // if interrupt handler is not null, call it
    {
        isr_t handler = interrupt_handlers[regs.int_no];       // get the interrupt handler
        handler(regs);                                         // call the interrupt handler
    }

}

