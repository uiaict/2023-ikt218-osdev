/*#define IRQ0 32
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
#define IRQ_COUNT 16

// Array to store IRQ handlers
void (*irq_handlers[IRQ_COUNT])(void);

// Initialize IRQ handlers
void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i] = NULL;
  }
}

// Register an IRQ handler
void register_irq_handler(int irq, void (*handler)(void)) {
  irq_handlers[irq] = handler;
}

// The main IRQ handler
void irq_handler(int irq) {
  // Check if a handler is registered for this IRQ
  if (irq_handlers[irq] != NULL) {
    irq_handlers[irq]();
  }

  // Send an EOI (End of Interrupt) signal to the PIC (Programmable Interrupt Controller)
  if (irq >= 8) {
    // Send EOI to the slave PIC
    outb(0xA0, 0x20);
  }
  // Send EOI to the master PIC
  outb(0x20, 0x20);
}struct idt_entry*/