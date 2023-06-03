#include "idt.h"
#include <string.h>



void init_idt() asm ("init_idt");
extern "C" {
    #include "print.h"
    extern void idt_load(uint32_t);
    void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
}


idt_entry_t idt[256];
idt_ptr_t idtp;

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t kernel, uint8_t flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFF;
    idt[num].sel = kernel;
    idt[num].always0 = 0;
    idt[num].flags   = flags  | 0x60;
    
}

//Implementation of memset based on: https://aticleworld.com/memset-in-c/
void *_memset(void *s, int c,  unsigned int len)
{
    unsigned char* p = (unsigned char*)s; //Only changed to be unsigned char because of type mismatch
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

void isr32_handler(){
    //ISR 32 does something
    print_str("ISR 32 interupting \n");
}

void isr33_handler(){
    //ISR 33 does something
    print_str("ISR 33 interupting \n");    
}

void isr34_handler(){
    //ISR 34 does something
    print_str("ISR 34 interupting \n");    
}
	
//Isrs. First 31 defined by intel
void init_interrupts(){
    idt_set_gate(32, (uint32_t)isr32_handler, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)isr33_handler, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)isr34_handler, 0x08, 0x8E);
}

/* Installs the IDT */
void init_idt()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    _memset(&idt, 0, sizeof(struct idt_entry) * 256);

    //init_interupts here
    init_interrupts();

    /* Points the processor's internal register to the new IDT */
    idt_load((uint32_t)&idtp);
}
	