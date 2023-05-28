// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.

// From James Molloy's kernel development tutorials: http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

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
