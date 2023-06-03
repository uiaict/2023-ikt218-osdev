#include <stdint.h>

/*
https://wiki.osdev.org/Interrupts_Tutorial
http://www.osdever.net/bkerndev/Docs/idt.htm

*/

/* Defines an IDT entry */
struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;       //kernel segment 
    uint8_t always0;     //always sset to 0
    uint8_t flags;      
    uint16_t  base_hi;
} __attribute__((packed));

typedef struct idt_entry idt_entry_t;

struct idt_ptr
{
    uint16_t  limit;
    uint32_t base;
} __attribute__((packed));

typedef struct idt_ptr idt_ptr_t;