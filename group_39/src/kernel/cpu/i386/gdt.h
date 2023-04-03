// 
// Writtten by IKT 218 Group 39 in the spring 2023. 


// stdint.h is a freestanding libc header file and can be used in our OS, even though we do not have POSIX support.
#include <stdint.h> 



// This is the header file for our Global Descriptor Table (GDT) implementation, which we will
// use to set up our memory segments. This will later allow us to enter Protected mode. 



// Here we define a struct which represents a GDT entry, called a segment descriptor.


// Our struct contains 6 fields

// **Limit low**: The lower 16 bits of the segment limit. 

// **Base Low**: The lower 16 bits of the base address. There are a total of 
// three base address fields because of backward compatibility with 16-bit processors. 

// **Base Middle**: The middle 8 bits of the base address


//// Base High: The last 8 bits of the base address.



// The __attribute__((packed)) is used to tell the compiler
// to not pack the struct. When a struct is packed, the compiler 
// may add padding to the struct to make it more memory efficient.
// But this may alter the size of the struct, causing memory alignment issues, which is 
// very much unwanted.


struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

