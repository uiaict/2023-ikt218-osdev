#include <stdint.h>  // Include the standard integer types

// Define a structure for an entry in the Interrupt Descriptor Table (IDT)
struct idt_entry {
    uint16_t base_low;  // Lower 16 bits of the address to jump to when this interrupt fires
    uint16_t selector;  // Kernel segment selector
    uint8_t reserved;  // This must always be zero
    uint8_t flags;  // More flags. Set using the SET_IDT_FLAG macro
    uint16_t base_high;  // The upper 16 bits of the address to jump to
} __attribute__((packed));  // This attribute forces GCC to avoid optimizing the layout of this struct, maintaining the ordering of fields as we defined

// Define a structure for the pointer to the array of IDT entries, this format is required by the 'lidt' instruction
struct idt_ptr {
    uint16_t limit;  // The upper bound of the array of IDT entries (size of IDT - 1)
    uint32_t base;  // The address of the first element in our idt_entry array
} __attribute__((packed));
