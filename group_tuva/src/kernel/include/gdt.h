//makes sure header file is only included once, preventing multiple declarations
#ifndef GDT_H
#define GDT_H

#include "common.h"

// This struct defines gdt_entry_struct, which represents a 
// single GDT entry. We use the attribute 'packed' to tell 
// GCC not to add any padding between members.
struct gdt_entry_struct
{
   u16int limit_low;           // The lower 16 bits of the limit.
   u16int base_low;            // The lower 16 bits of the base.
   u8int  base_middle;         // The next 8 bits of the base.
   u8int  access;              // Access flags, determine what ring this segment can be used in.
   u8int  granularity;
   u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

//This struct defines the gdt_ptr_struct, which represents the
// GDT pointer, consisting of a limit and a base.
struct gdt_ptr_struct
{
   u16int limit;               // The upper 16 bits of all selector limits.
   u32int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;


// Extern C declaration, allowing cpp code to call C functions
// without name mangling.
#ifdef __cplusplus
extern "C" {
#endif

// Declares the init_descriptor_tables function, which
// initializes the GDT (and IDT).
void init_descriptor_tables();

// End of the extern C declaration
#ifdef __cplusplus
}
#endif

// Ends the ifndef statement
#endif // GDT_H
