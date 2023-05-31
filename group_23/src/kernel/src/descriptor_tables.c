#include "../include/descriptor_tables.h"
#include "../include/common.h"
#include "../include/isr.h"

//access ASM functions from gdt_load.asm

extern void gdt_flush(uint32_t); 
extern void idt_flush(uint32_t);

// functions
static void gdt_init();
static void idt_init();
static void gdt_descriptors(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
static void idt_descriptors(uint8_t num,uint32_t base ,uint16_t sel,uint8_t flags);

//gdt entries
gdt_entry_t gdt_entries[GDT_ENTRIES];                      //array of gdt entries 
gdt_ptr_t   gdt_ptr;                                       //pointer to gdt entries

// IDT entries
idt_entry_t idt_entries[IDT_ENTRIES];                      //array of idt entries
idtr_t      idtr;                                          //pointer to idt entries

// ISR handlers
extern isr_t interrupt_handlers[];                         //array of interrupt handlers

// initialize descriptor tables
void init_descriptor_tables()
{
    gdt_init();
    idt_init();

    // Nullify all the interrupt handlers
    memset(&interrupt_handlers, 0, sizeof(isr_t)*ISR_SIZE);
}

// initialize GDT with 5 descriptors, parameters passed to gdt_descriptor function
void gdt_init()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1; //size of gdt entries
    gdt_ptr.base = (uint32_t)&gdt_entries;                   //base address of gdt entries, takes the adress of the actual GDT entries

    gdt_descriptors(0, 0, 0, 0, 0);                          // Null segment
    gdt_descriptors(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);           // Code segment
    gdt_descriptors(2, 0, 0xFFFFFFFF, 0x92, 0xCF);           // Data segment
    gdt_descriptors(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);           // User mode code segment
    gdt_descriptors(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);           // User mode data segment

    // flush old GDT implemented by GRUB and load new GDT from ASM file
    gdt_flush((uint32_t)&gdt_ptr); 
}

// set values for GDT entries
void gdt_descriptors(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);              // 16 bit base address      
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;       // 8 bits of middle base address, shifted by 16 bits   
    gdt_entries[num].base_high = (base >> 24) & 0xFF;         // 8 bits of high base address, shifted by 24 bits

    gdt_entries[num].limit_low = (limit & 0xFFFF);            // 16 bit limit
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);    // 4 bits limit  of granularity field, shifted by 16 bits

    gdt_entries[num].granularity |= (gran & 0xF0);            // upper 4 bits of granularity field
    gdt_entries[num].access = access;                         // access flags
}

// initialize IDT with 256 entries
void idt_init()
{
    idtr.limit = sizeof (idt_entry_t) * IDT_ENTRIES - 1;      //idt entries limit
    idtr.base = (uint32_t) &idt_entries;                      //idt entries base address

    memset(&idt_entries, 0, sizeof(idt_entry_t)*IDT_ENTRIES); //set all entries in idt_entries to 0

    // remapping the PIC to communicate with CPU interrupt pin via I/O bus. 
    outb(0x20, 0x11);                                         // IO base adress for master command port 0x20, and inizialization command 0x11   
    outb(0xA0, 0x11);                                         // IO base adress for slave command port 0xA0, and inizialization command 0x11
    outb(0x21, 0x20);                                         // Master data adr 0x21, remap offset 0x20
    outb(0xA1, 0x28);                                         // Slave data adr 0xA1, remap offset 0x28
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Call to idt_descriptors function to set values for each entry in idt_entries, and set IDT gates for IRQ handlers
    idt_descriptors( 0, (uint32_t)isr0 , 0x08, 0x8E);         // index 0, adress of isr0 (interrupt handler function), segment selector 0x08 (kernel code segment), flags 0x8E
    idt_descriptors( 1, (uint32_t)isr1 , 0x08, 0x8E);
    idt_descriptors( 2, (uint32_t)isr2 , 0x08, 0x8E);
    idt_descriptors( 3, (uint32_t)isr3 , 0x08, 0x8E);
    idt_descriptors( 4, (uint32_t)isr4 , 0x08, 0x8E);
    idt_descriptors( 5, (uint32_t)isr5 , 0x08, 0x8E);
    idt_descriptors( 6, (uint32_t)isr6 , 0x08, 0x8E);
    idt_descriptors( 7, (uint32_t)isr7 , 0x08, 0x8E);
    idt_descriptors( 8, (uint32_t)isr8 , 0x08, 0x8E);
    idt_descriptors( 9, (uint32_t)isr9 , 0x08, 0x8E);
    idt_descriptors(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_descriptors(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_descriptors(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_descriptors(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_descriptors(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_descriptors(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_descriptors(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_descriptors(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_descriptors(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_descriptors(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_descriptors(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_descriptors(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_descriptors(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_descriptors(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_descriptors(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_descriptors(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_descriptors(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_descriptors(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_descriptors(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_descriptors(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_descriptors(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_descriptors(31, (uint32_t)isr31, 0x08, 0x8E);
    idt_descriptors(32, (uint32_t)irq0 , 0x08, 0x8E);
    idt_descriptors(33, (uint32_t)irq1 , 0x08, 0x8E);
    idt_descriptors(34, (uint32_t)irq2 , 0x08, 0x8E);
    idt_descriptors(35, (uint32_t)irq3 , 0x08, 0x8E);
    idt_descriptors(36, (uint32_t)irq4 , 0x08, 0x8E);
    idt_descriptors(37, (uint32_t)irq5 , 0x08, 0x8E);
    idt_descriptors(38, (uint32_t)irq6 , 0x08, 0x8E);
    idt_descriptors(39, (uint32_t)irq7 , 0x08, 0x8E);
    idt_descriptors(40, (uint32_t)irq8 , 0x08, 0x8E);
    idt_descriptors(41, (uint32_t)irq9 , 0x08, 0x8E);
    idt_descriptors(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_descriptors(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_descriptors(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_descriptors(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_descriptors(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_descriptors(47, (uint32_t)irq15, 0x08, 0x8E);
    

  

    idt_flush((uint32_t)&idtr);                                 // Call to idt_flush function to load the IDT register with the new values

}

//define entries
static void idt_descriptors(uint8_t num,uint32_t base ,uint16_t sel,uint8_t flags)
{
    idt_entries[num].base_low  = (base & 0xFFFF);               // jump to lower 16 bits adress when interrupt occurs
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;         // jump to higher 16 bits when interrupt occurs
    idt_entries[num].selector  = sel;                           // kernel segment selector
    idt_entries[num].zero      = 0;                             // always zero
    idt_entries[num].flags     = flags;                         // flags
    
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
