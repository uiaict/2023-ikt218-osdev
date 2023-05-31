#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_NUM_ENTRIES 256
#define IRQ_TOTAL_COUNT 16

#define INTERRUPT_SERVICE_ROUTINE(n) ((n) < IRQ0 ? (n) : -1)
#define INTERRUPT_REQUEST(n) ((n) < IRQ_TOTAL_COUNT ? (IRQ0 + (n)) : -1)

extern "C" {
    extern void service_routine_handler_array[32]();
    extern void interrupt_request_handler_array[16]();
}

struct idt_descriptor
{
    uint16_t base_lower;
    uint16_t segment_selector;
    uint8_t always_zero;
    uint8_t flags;
    uint16_t base_upper;
} __attribute__((packed));

struct idt_descriptor_pointer
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct register_values
{
    uint32_t data_segment_selector;
    uint32_t edi, esi, ebp, unused, ebx, edx, ecx, eax;
    uint32_t interrupt_number, error_code;
    uint32_t eip, cs, eflags, esp, ss;
};

typedef void (*isr_handler_type)(register_values*, void*);

struct interrupt_handler
{
    int number;
    isr_handler_type handler;
    void *data;
};

static interrupt_handler interrupt_handler_array[IDT_NUM_ENTRIES];
static interrupt_handler irq_handler_array[IRQ_TOTAL_COUNT];

void initialize_idt();
void enable_interrupts();
void initialize_irq();
void set_up_interrupt_handlers();
void set_up_irq_handlers();
void set_idt_gate(uint8_t number, uint32_t base, uint16_t selector, uint8_t flags);
void assign_irq_handler(int irq, isr_handler_type handler, void* context);
void assign_interrupt_handler(uint8_t number, isr_handler_type handler, void* context);
void handle_service_routine(register_values regs);

#endif /* IDT_H */
