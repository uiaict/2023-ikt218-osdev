

#ifndef UIAOS_IDT_H
#define UIAOS_IDT_H
#include <stdint.h>
#include<string.h>
#define NUM_IDT_ENTRIES 256

struct idt_entry_struct
{
    uint16_t base_lo;     // memmory address        
    uint16_t sel;                
    uint8_t  always0;            
    uint8_t  flags;         // acess level   
    uint16_t base_hi;        // memmory address        
};

typedef struct idt_entry_struct idt_entry_t;


struct idt_ptr_struct
{
    uint16_t limit; // size
    uint32_t base;    // memory address            
} __attribute__((packed)); // packed is so compizer dont omptize away vital information

typedef struct idt_ptr_struct idt_ptr_t;

#endif