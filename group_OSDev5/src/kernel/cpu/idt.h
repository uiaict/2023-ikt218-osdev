#ifndef UIAOS_IDT_H
#define UIAOS_IDT_H
#include <stdint.h>

#define NUM_IDT_ENTRIES 256

// A struct describing an interrupt gate.
struct idt_entry_struct
{
    uint16_t base_lo;               // The lower 16 bits of the address to jump to when this interrupt fires.
    uint16_t sel;                   // Kernel segment selector that this IDT entry will use.
    uint8_t  always0;               // This must always be zero because unused bits in the descriptor are used by the hardware for additional features
    uint8_t  flags;                 // Flags - for example, this indicates whether this is an interrupt gate or a trap gate.
    uint16_t base_hi;               // The upper 16 bits of the address to jump to.
};

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// Suitable for giving to 'lidt'.
struct idt_ptr_struct
{
    uint16_t limit;                 // The upper 16 bits of all selector limits.
    uint32_t base;                  // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

#endif //UIAOS_IDT_H