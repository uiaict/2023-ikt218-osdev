#include <stddef.h>

#include "common.h"
#include "interrupts.h"

/* Called from our ASM interrupt handler stub. */
extern void irq_handler(struct registers regs);

void irq_init()
{
    for (uint8_t i = 0; i < IRQ_COUNT; i++) {
        irq_handlers[i].handler = NULL;
        irq_handlers[i].num = i;
    }
}

void register_irq_handler(uint8_t n, isr_t handler)
{
    irq_handlers[n].handler = handler;
}

/* Send an EOI (end-of-interrupt) signal to the PICs. */
void irq_handler(struct registers regs)
{
    if (regs.int_no >= 40)
        output_to_port(PIC2_CMD, PIC_EOI);
    output_to_port(PIC1_CMD, PIC_EOI);

    struct int_handler intrpt = irq_handlers[regs.int_no];
    if (intrpt.handler != 0)
        intrpt.handler(&regs);
}
