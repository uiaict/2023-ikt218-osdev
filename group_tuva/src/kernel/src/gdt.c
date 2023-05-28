#include "common.h"
#include "gdt.h"
#include "stdio.h"
#include "idt.h"
#include "system.h"

// Declares the external asm function gdt_flush
extern void gdt_flush(u32int);
extern void idt_flush(u32int);

// Declaration of internal static functions
static void init_gdt();
static void gdt_set_gate(s32int,u32int,u32int,u8int,u8int);
static void init_idt();
static void idt_set_gate(u8int,u32int,u16int,u8int);

// Declares array of 5 GDT entries and a GDT pointer
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void init_descriptor_tables()
{
   // Initialise the global descriptor table.
   init_gdt();
   init_idt();
}

static void init_gdt()
{
   // Sets GDT pointer limit to total size of GDT entries - 1,
   // sets GDT pointer base to the address of the first GDT entry.
   gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
   gdt_ptr.base  = (u32int)&gdt_entries;

   // Sets the GDT entries for the null segment, code segment, 
   // data segment, and user mode data segment 
   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   // Calls the gdt_flush function with the address of the GDT
   // pointer to load the new GDT and update the segment registers.
   gdt_flush((u32int)&gdt_ptr);
}

// Set the value of one GDT entry.
static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
   // Sets the base address of the GDT entry 
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (u8int)(base >> 24) & 0xFF;

   // Sets the limit of the GDT entry
   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   // Sets the granularity and access flags of the GDT entry
   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}

static void init_idt()
{
   idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
   idt_ptr.base  = (uint32_t)&idt_entries;

   memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

   //remap the irq table.
   outb(0x20, 0x11);
   outb(0xA0, 0x11);
   outb(0x21, 0x20);
   outb(0xA1, 0x28);
   outb(0x21, 0x04);
   outb(0xA1, 0x02);
   outb(0x21, 0x01);
   outb(0xA1, 0x01);
   outb(0x21, 0x0);
   outb(0xA1, 0x0);

   idt_set_gate( 0, (uint32_t)isr0 , 0x08, 0x8E);
   idt_set_gate( 1, (uint32_t)isr1 , 0x08, 0x8E);
   idt_set_gate( 2, (uint32_t)isr2 , 0x08, 0x8E);
   idt_set_gate( 3, (uint32_t)isr3 , 0x08, 0x8E);
   idt_set_gate( 4, (uint32_t)isr4 , 0x08, 0x8E);
   idt_set_gate( 5, (uint32_t)isr5 , 0x08, 0x8E);
   idt_set_gate( 6, (uint32_t)isr6 , 0x08, 0x8E);
   idt_set_gate( 7, (uint32_t)isr7 , 0x08, 0x8E);
   idt_set_gate( 8, (uint32_t)isr8 , 0x08, 0x8E);
   idt_set_gate( 9, (uint32_t)isr9 , 0x08, 0x8E);
   idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
   idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
   idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
   idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
   idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
   idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
   idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
   idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
   idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
   idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
   idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
   idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
   idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
   idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
   idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
   idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
   idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
   idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
   idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
   idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
   idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
   idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

   idt_flush((u32int)&idt_ptr);
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
   idt_entries[num].base_lo = base & 0xFFFF;
   idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   idt_entries[num].sel     = sel;
   idt_entries[num].always0 = 0;
   // We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3.
   idt_entries[num].flags   = flags /* | 0x60 */;
}
