#ifndef ESOS_IDT_H
#define ESOS_IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256
namespace ESOS::IDT
{
    // Define the IDT entry structure
    struct idt_entry_t {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
    } __attribute__((packed));

    // Define the GDT and IDT pointers

    struct idt_ptr_t {
    uint16_t limit;
    uint32_t base;
    } __attribute__((packed));

    typedef struct registers
    {
        uint32_t ds;                  // Data segment selector
        uint32_t edi, esi, ebp, useless_value, ebx, edx, ecx, eax; // Pushed by pusha.
        uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
        uint32_t eip, cs, eflags, esp, ss; // Pushed by the processor automatically.
    } registers_t;


    // Enables registration of callbacks for interrupts or IRQs.
    // For IRQs, to ease confusion, use the #defines above as the
    // first parameter.
    typedef void (*isr_t)(registers_t*, void*);

    // Structure to hold information about an interrupt handler
    struct int_handler_t {
    int num;
    isr_t handler;
    void *data;
    };


    void init_idt();

}
#endif