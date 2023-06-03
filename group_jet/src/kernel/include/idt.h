#include <stdint.h> 
#include "common.h"
#include "stdio.h"

#define IDT_ENTRIES 256

struct idt_entry_t
{
    uint16_t selector;
    uint16_t low_base;
    uint8_t flags;
    uint8_t zero;  
    uint16_t high_base;
}__attribute__((packed));

struct idt_ptr_t
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct int_handler {
    void (*handler)(void *data);
    int num;
    void *data; 
};


void init_idt();