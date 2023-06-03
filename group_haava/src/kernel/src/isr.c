#include "interrupts.h"
#include "system.h"

extern void isr_handler(struct registers regs);

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    int_handlers[n].handler = handler;
}

void isr_handler(struct registers regs)
{
    uint8_t int_no = regs.int_no & 0xFF;
    struct int_handler intrpt = int_handlers[int_no];
    if (intrpt.handler != 0) {
        intrpt.handler(&regs);
    } else {
        printf("unhandled interrupt\n");
    }
}
