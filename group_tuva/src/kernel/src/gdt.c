#include "common.h"
#include "gdt.h"
#include "stdio.h"

// Declares the external asm function gdt_flush
extern void gdt_flush(u32int);

// Declaration of internal static functions
static void init_gdt();
static void gdt_set_gate(s32int,u32int,u32int,u8int,u8int);

// Declares array of 5 GDT entries and a GDT pointer
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
//idt_entry_t idt_entries[256];
//idt_ptr_t   idt_ptr;

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void init_descriptor_tables()
{
   // Initialise the global descriptor table.
   init_gdt();
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
