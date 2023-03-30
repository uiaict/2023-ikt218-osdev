#ifndef ESOS_IDT_H
#define ESOS_IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256
namespace ESOS::IDT
{
    // Define the IDT entry structure
    struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
    } __attribute__((packed));

    // Define the GDT and IDT pointers

    struct idt_ptr {
    uint16_t limit;
    uint32_t base;
    } __attribute__((packed));

    // Structure to hold information about an interrupt handler
    struct int_handler {
    int num;
    isr_t handler;
    void *data;
    };


    void init_idt();

}
#endif