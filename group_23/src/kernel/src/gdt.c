#include "gdt.h"
#include <stdint.h>
#include "system.h"
#include <stdbool.h>
#include "gdt.h"



struct gdt_entry gdt_descriptor[GDT_ENTRIES];
struct gdt_ptr gdt_ptr;

void gdt_descriptors(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_descriptor[num].base_low = (base & 0xFFFF); 
    gdt_descriptor[num].base_middle = (base >> 16) & 0xFF; 
    gdt_descriptor[num].base_high = (base >> 24) & 0xFF;

    gdt_descriptor[num].limit_low = (limit & 0xFFFF);
    gdt_descriptor[num].granularity = ((limit >> 16) & 0x0F);

    gdt_descriptor[num].granularity |= (gran & 0xF0);
    gdt_descriptor[num].access = access;
}


/*void gdt_load(struct gdt_ptr *gp)
{
    asm volatile("lgdt (%0)" : : "r" (gp)); 
}*/

void gdt_init() asm ("gdt_init"); 
void gdt_init()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gdt_ptr.base = (uint32_t)&gdt_descriptor;

    gdt_descriptors(0, 0, 0, 0, 0); // Null segment
    gdt_descriptors(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_descriptors(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_descriptors(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_descriptors(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    //gdt_load(&gdt_ptr);

    //flush old GDT implemented by GRUB and load new GDT
    gdt_flush((uint32_t)&gdt_ptr); 
}

bool check_gdt_init()
{
    uint16_t gdt_limit; 
   // uint32_t gdt_base; 
    uint32_t cr0; //Control register 0 

    //get current value of cr0 
    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));  
    
    //check if first bit is set (protected mode)
    if (cr0 & 0x1)
    {
        __asm__ volatile ("sgdt %0" : "=m" (gdt_ptr));

        gdt_limit = gdt_ptr.limit; 
      //  gdt_base = gdt_ptr.base; 

        // if gdt != 0, the gdt is initialized
        if (gdt_limit != 0)
        {
            return true; 
        }
       
        
    }
    return false; 
}
