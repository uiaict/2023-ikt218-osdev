// 
// Written by IKT218 Group 39 in the spring 2023. 


// This is the header file for our Global Descriptor Table (GDT) implementation, which we will
// use to set up our memory segments. This will later allow us to enter Protected mode. 



// Adding ifndef to avoid include errors.
#ifndef UIAOS_GDT_H
#define UIAOS_GDT_H



// stdint.h is a freestanding libc header file and can be used in our OS, even though we do not have POSIX support.
// We use some of the types that it define, like uint16_t - which is a fixed width data types. 
#include <stdint.h> 




// Our GDT entry (segment descriptor) struct. 
struct gdt_entry {
    uint16_t limit_low; // The lower 16 bits of the segment limit
    uint16_t base_low; // The lower 16 bits of the base address. 
    uint8_t base_middle; // The middle 8 bits of the base address. 
    uint8_t access; // 8 bit field that represents several different access flags, e.g. if the segment is currently in memory (present bit).
    uint8_t granularity; // 8 bit field that sets the granularity of the size of the segment, e.g. if it is divided into 4KB pages or if the size is set in bytes.
    uint8_t base_high; // The upper 8 bits of the base address.
} __attribute__((packed)); // This attribute tells the compiler to not add padding to the struct, which would increase its size. 


// The GDT pointer struct which will be contained in the GDT register.
struct gdt_pointer {
    uint16_t limit; // 16 bit limit address (the bounds of the GDT table)
    uint32_t base; //  32 bit base address (where the GDT table begins in memory)
} __attribute__((packed)); // As above, tell the compiler not to add padding.

#endif