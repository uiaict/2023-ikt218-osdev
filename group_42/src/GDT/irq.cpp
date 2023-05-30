
#include <stdint.h>
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
#define NULL nullptr

#define IRQ_COUNT 16


void (*irq_handlers[IRQ_COUNT])(void);


void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i] = NULL;
  }
}
void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__("outb %0, %1" : : "a"(value), "Nd"(port));
}

void register_irq_handler(int irq, void (*handler)(void)) {
  irq_handlers[irq] = handler;
}


void irq_handler(int irq) {
 
  if (irq_handlers[irq] != NULL) {
    irq_handlers[irq]();
  }

 
  if (irq >= 8) {

    outb(0xA0, 0x20);
  }

  outb(0x20, 0x20);
}struct idt_entry;