// #include "../../../stdlib/include/system.h"
#include "hardware_port.h"
// #include "../../../stdlib/include/system.h"
#include "../../include/print.h"
#include "isr.h"
// #include "memory.h"
#include <cstddef>
#include "../../memory/kmalloc.h"



extern "C"{
    void *memset(void *s, int c, size_t n);
    // void init_isr() asm("init_isr");
    void irq_handler(registers_t regs) asm("irq_handler");
    void isr_handler(registers_t regs) asm("isr_handler");
    // void init_isr();
}

interrupt_t interrupt_handlers[256];


void init_isr(){
    // Nullify all the interrupt handlers.
    // printf("\n");
    // print_int(reinterpret_cast<uint32_t>(&interrupt_handlers[0]));
    // printf("\n");
    // print_int(reinterpret_cast<uint32_t>(&interrupt_handlers[255]));
    // printf("\n");

    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}

void register_interrupt_handler(uint8_t n, isr_t handler, void* context)
{
    interrupt_handlers[n].handler = handler;
    interrupt_handlers[n].context = context;
    // print_int(reinterpret_cast<int>(&interrupt_handlers[14]));
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    uint8_t int_no = regs.int_no & 0xFF;
    interrupt_t intrpt = interrupt_handlers[int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.context);
    }
    else
    {
        printf("unhandled interrupt: ");
        print_uint8(int_no);
        printf("\n");

        for(;;);
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

    interrupt_t intrpt = interrupt_handlers[regs.int_no];
    if (intrpt.handler != 0)
    {
        intrpt.handler(&regs, intrpt.context);
    }

}
