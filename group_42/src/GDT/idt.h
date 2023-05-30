

#ifndef UIAOS_IDT_H
#define UIAOS_IDT_H
#include <stdint.h>
#include<string.h>
#define NUM_IDT_ENTRIES 256

struct idt_entry_struct
{
    uint16_t base_lo;             
    uint16_t sel;                
    uint8_t  always0;            
    uint8_t  flags;            
    uint16_t base_hi;           
};

typedef struct idt_entry_struct idt_entry_t;


struct idt_ptr_struct
{
    uint16_t limit;
    uint32_t base;                
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

#endif