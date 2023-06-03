#ifndef GDT_H
#define GDT_H

#include <stdint.h>




// Define the number of entries in the GDT
#define GDTSIZE 8

// Define the location where the GDT will be stored in memory
#define GDTBASE 0x00000800

// Define a structure for the GDT descriptor
struct gdtdesc {
    uint16_t lim0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t acces;
    uint8_t lim16_19:4;
    uint8_t other:4;
    uint8_t base24_31;
} __attribute__((packed));

// Define a structure for the GDTR (GDT register)
struct gdtr {
    uint16_t limite;
    uint32_t base;
} __attribute__((packed));



struct tss {
    uint16_t back_link, __blh;
    uint32_t esp0;
    uint16_t ss0, __ss0h;
    uint32_t esp1;
    uint16_t ss1, __ss1h;
    uint32_t esp2;
    uint16_t ss2, __ss2h;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp;
    uint32_t esi, edi;
    uint16_t es, __esh;
    uint16_t cs, __csh;
    uint16_t ss, __ssh;
    uint16_t ds, __dsh;
    uint16_t fs, __fsh;
    uint16_t gs, __gsh;
    uint16_t ldt_selector, __ldtselh;
    uint16_t debug_flag, io_map;
};

// Initialize the GDT
void init_gdt(void);
// Initialize a GDT segment descriptor
void init_gdt_desc(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdtdesc *desc);


//extern void gdt_flush();

#endif // GDT_H