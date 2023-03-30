#include "system.h"
#ifndef GDT_H
#define GDT_H
#include <stdint.h>
#include <stdbool.h>
#define GDT_ENTRIES 5


struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)); //so that gcc use as little memory as possible

//Local descriptor table pointer
struct gdt_ptr 
{
    uint16_t limit; //16 bit limit. Size of the GDT
    uint32_t base; //32 bit pointer. First entry in GDT
} __attribute__((packed));


//void gdt_init();
//void gdt_load(struct gdt_ptr *gdt_ptr);

void gdt_seg_descriptor(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

//function to check if gdt is initialized
//bool check_gdt_init(); 
//function in gdt.asm to reload new segment registers
extern void gdt_flush();

#endif /* GDT_H */

