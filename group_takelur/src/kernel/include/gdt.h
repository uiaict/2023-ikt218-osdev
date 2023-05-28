// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.

// From James Molloy's kernel development tutorials: http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

#ifndef GDT_H
#define GDT_H


struct gdt_entry_struct
{
   u16int limit_low;           // The lower 16 bits of the limit.
   u16int base_low;            // The lower 16 bits of the base.
   u8int  base_middle;         // The next 8 bits of the base.
   u8int  access;              // Access flags, determine what ring this segment can be used in.
   u8int  granularity;         // Granularity flags, specify the scaling of the segment limit.
   u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));     // Packed prevents GCC from changing any alignment
typedef struct gdt_entry_struct gdt_entry_t; 

// This struct describes a GDT pointer that points to the start of the array of GDT entries.
struct gdt_ptr_struct
{
   u16int limit;               // The upper 16 bits of all selector limits. (Size of table - 1)
   u32int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t; 

extern void gdt_flush(u32int); // This is in gdt.asm

// Initialisation function is publicly accessible.
extern void init_gdt(); 

#endif