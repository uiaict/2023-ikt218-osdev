#ifndef IRQ_H
#define IRQ_H

extern void irq_ack(int irq);
extern void irq_handler(registers_t regs);
extern void init_irq_handlers();

#endif