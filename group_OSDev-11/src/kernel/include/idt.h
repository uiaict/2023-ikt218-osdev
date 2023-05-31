#ifndef IDT_H
#define IDT_H
#include <stdint.h>

#define IDT_ENTRIES 256
#define IRQ_COUNT 16

enum INTERRUPT_SERVICE_ROUTINES {
    ISR0 = 0, ISR1, ISR2, ISR3, ISR4, ISR5, ISR6, ISR7, ISR8, ISR9,
    ISR10, ISR11, ISR12, ISR13, ISR14, ISR15, ISR16, ISR17, ISR18, ISR19,
    ISR20, ISR21, ISR22, ISR23, ISR24, ISR25, ISR26, ISR27, ISR28, ISR29,
    ISR30, ISR31,
    IRQ0 = 32, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7, IRQ8, IRQ9,
    IRQ10, IRQ11, IRQ12, IRQ13, IRQ14, IRQ15
};

extern "C" {
    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr20();
    extern void isr21();
    extern void isr22();
    extern void isr23();
    extern void isr24();
    extern void isr25();
    extern void isr26();
    extern void isr27();
    extern void isr28();
    extern void isr29();
    extern void isr30();
    extern void isr31();

    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();
}

// idt entry
struct idt_entry 
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

// idt pointer
struct idt_ptr 
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct registers
{
    uint32_t ds;                                                    // Data segment selector
    uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; 
    uint32_t int_no, err_code;                                      // Interrupt number and error code
    uint32_t eip, cs, eflags, esp, ss; 
};

typedef void (*isr_t)(registers*, void*);

// interrupt handler
struct int_handler 
{
    int num;
    isr_t handler;
    void *data;
};

static struct int_handler int_handlers[IDT_ENTRIES];
static struct int_handler irq_handlers[IRQ_COUNT];

void idt_init();
void init_interrupts();
void irq_init();
void init_interrupt_handlers();
void init_irq_handlers();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void register_irq_handler(int irq, isr_t handler, void* ctx);
void register_interrupt_handler(uint8_t n, isr_t handler, void* context);
void isr_handler(registers regs);

#endif
