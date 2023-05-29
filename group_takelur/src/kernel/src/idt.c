//
// descriptor_tables.c - Initialises the GDT and IDT, and defines the
// default ISR and IRQ handler.
// Based on code from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
// http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html


#include "idt.h"
#include "common.h"

// Access the ASM function to flush IDT.
extern void idt_flush(u32int);

// Prototype
static void idt_set_gate(u8int,u32int,u16int,u8int);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;


void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;        // Limit for IDT (256 entries)
    idt_ptr.base  = (u32int)&idt_entries;                // Base address for IDT

    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);    // Zero out the IDT

    // Remap the irq table.
    // See http://wiki.osdev.org/8259_PIC#Initialisation
    outb(0x20, 0x11);   // Send ICW1 to master PIC
    outb(0xA0, 0x11);   // Send ICW1 to slave PIC
    outb(0x21, 0x20);   // Send ICW2 to master PIC (IRQ 0-7 mapped to IDT entries 0x20-0x27)
    outb(0xA1, 0x28);   // Send ICW2 to slave PIC (IRQ 8-15 mapped to IDT entries 0x28-0x2F)
    outb(0x21, 0x04);   // Send ICW3 to master PIC (slave PIC at IRQ2)
    outb(0xA1, 0x02);   // Send ICW3 to slave PIC (slave PIC cascade identity 2)
    outb(0x21, 0x01);   // Send ICW4 to master PIC
    outb(0xA1, 0x01);   // Send ICW4 to slave PIC
    outb(0x21, 0x0);    // Disable all IRQs on master PIC
    outb(0xA1, 0x0);    // Disable all IRQs on slave PIC

    // Set individual gates in the IDT (0x08 = kernel code segment, 0x8E = flag with present bit set)
    idt_set_gate( 0, (u32int)isr0 , 0x08, 0x8E);     
    idt_set_gate( 1, (u32int)isr1 , 0x08, 0x8E);     
    idt_set_gate( 2, (u32int)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (u32int)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (u32int)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (u32int)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (u32int)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (u32int)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (u32int)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (u32int)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (u32int)isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32int)isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32int)isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32int)isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32int)isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32int)isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32int)isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32int)isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32int)isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32int)isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32int)isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32int)isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32int)isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32int)isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32int)isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32int)isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32int)isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32int)isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32int)isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32int)isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32int)isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32int)isr31, 0x08, 0x8E);

    // Load IDT by calling ASM flush function
    idt_flush((u32int)&idt_ptr);
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;           // Lower 16 bits of base address
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;   // Higher 16 bits of base address

    idt_entries[num].sel     = sel;                     // Kernel segment selector
    idt_entries[num].always0 = 0;                       // Reserved field is always 0

    idt_entries[num].flags   = flags /* | 0x60 */;      // Set flags
} 